//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::TcpClientServer
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_TcpClientServer__hpp
#define INC__Bt_Com_TcpClientServer__hpp

#include <Arduino.h>

#include "Bt/Workcycle/I_Runnable.hpp"
#include "I_RequestServer.hpp"
#include "StaticArrayPackageBuffer.hpp"
#include "BinaryInputPackage.hpp"
#include "BinaryOutputPackage.hpp"

namespace Bt {
namespace Com {


template<typename Socket>
class TcpClientServer : public Workcycle::I_Runnable
{
   public:

      enum { TCP_SERVER_BUFFER_LENGHT = 32};
      enum { TCP_SERVER_START_REQUEST    = 0xAF};
      enum { TCP_SERVER_QUIT             = 0xAA};


      TcpClientServer(Socket& iSocket, const char* iHost, uint16_t iPort, I_RequestServer& iHandler);
      ~TcpClientServer();
   
      virtual void workcycle();

   private:
   	  // Constructor to prohibit copy construction.
      TcpClientServer(const TcpClientServer&);

      // Operator= to prohibit copy assignment
      TcpClientServer& operator=(const TcpClientServer&);

      void connect();
      void waitForRequest();
      void readSize();
      void readData();
      void sendData();

      bool checkReadSocket();
      bool checkData(int iData);

      typedef void (TcpClientServer<Socket>::*StateFunction)();

      Socket* mSocket;
      const char *mHost;
      uint16_t mPort;
      StateFunction mStateFunction;
      I_RequestServer* mHandler;

      size_t mSize;

      StaticArrayPackageBuffer<TCP_SERVER_BUFFER_LENGHT> mInputBuffer;
      BinaryInputPackage mInput;
      StaticArrayPackageBuffer<TCP_SERVER_BUFFER_LENGHT> mOutputBuffer;
      BinaryOutputPackage mOutput;

};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

template<typename Socket>
TcpClientServer<Socket>::TcpClientServer(Socket& iSocket, const char* iHost, uint16_t iPort, I_RequestServer& iHandler)
: mSocket(&iSocket), mHost(iHost), mPort(iPort), mStateFunction(&TcpClientServer<Socket>::connect), mHandler(&iHandler), mSize(0) , mInput(mInputBuffer), mOutput(mOutputBuffer) {
}

//-------------------------------------------------------------------------------------------------

template<typename Socket>
TcpClientServer<Socket>::~TcpClientServer() {

}

//-------------------------------------------------------------------------------------------------

template<typename Socket>
void TcpClientServer<Socket>::workcycle() {
   (this->*mStateFunction)();
}

//-------------------------------------------------------------------------------------------------

template<typename Socket>
void TcpClientServer<Socket>::connect() {
   Serial.println("try connect ...");
   if (mSocket->connect(mHost, mPort) ) {
      mStateFunction = &TcpClientServer<Socket>::waitForRequest;
      Serial.println(" ... ok!");
   } else {
      Serial.println(" ... failed!");
   }
}


//-------------------------------------------------------------------------------------------------

template<typename Socket>
void TcpClientServer<Socket>::waitForRequest() {
   if (!checkReadSocket()) {
      return;
   }

   int commandByte = mSocket->read();

   if (!checkData(commandByte)) {
      return;
   }

   if (commandByte == TCP_SERVER_START_REQUEST) {
      mStateFunction = &TcpClientServer<Socket>::readSize;
      return;
   }

   if (commandByte == TCP_SERVER_QUIT) {
      mSocket->stop();
      mStateFunction = &TcpClientServer<Socket>::connect;
      return;
   }

}

//-------------------------------------------------------------------------------------------------

template<typename Socket>
void TcpClientServer<Socket>::readSize() {
   if (!checkReadSocket()) {
      return;
   }

   int size = mSocket->read();
   if (!checkData(size)) {
      return;
   }

   mSize = size;
   mInputBuffer.clear();
   mStateFunction = &TcpClientServer<Socket>::readData;
}


//-------------------------------------------------------------------------------------------------

template<typename Socket>
void TcpClientServer<Socket>::readData() {
   if (!checkReadSocket()) {
      return;
   }

   int data = mSocket->read();
   if (!checkData(data)) {
      return;
   }

   mInputBuffer.put(data);

   if(mInputBuffer.length() < mSize) {
      return;
   }

   mOutputBuffer.clear();

   mHandler->handleRequest(mInput,mOutput);
   mStateFunction = &TcpClientServer<Socket>::sendData;
}

//-------------------------------------------------------------------------------------------------

template<typename Socket>
void TcpClientServer<Socket>::sendData() {

   mSocket->write(TCP_SERVER_START_REQUEST);
   mSocket->write(mOutputBuffer.length());
   if (mOutputBuffer.length() > 0) {
      mSocket->write(mOutputBuffer.raw(),mOutputBuffer.length());
   }
   mStateFunction = &TcpClientServer<Socket>::waitForRequest;

}

//-------------------------------------------------------------------------------------------------

template<typename Socket>
bool TcpClientServer<Socket>::checkData(int iData) {
   if (iData < 0) {
      if (!mSocket->connected()) {
         mSocket->flush();
         mSocket->stop();
         mStateFunction = &TcpClientServer::connect;
         return false;
      }
      return false;
   }
   return true;
}

//-------------------------------------------------------------------------------------------------

template<typename Socket>
bool TcpClientServer<Socket>::checkReadSocket() {
   if (!mSocket->connected()) {
      mSocket->flush();
      mSocket->stop();
      mStateFunction = &TcpClientServer<Socket>::connect;
      return false;
   }
   int available = mSocket->available();
   if (available <= 0) {
      return false;
   }

   return true;
}

//-------------------------------------------------------------------------------------------------


} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_TcpClientServer__hpp
