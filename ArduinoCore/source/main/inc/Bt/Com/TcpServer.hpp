//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::TcpServer
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_TcpServer__hpp
#define INC__Bt_Com_TcpServer__hpp

#include "I_RequestServer.hpp"
#include "StaticArrayPackageBuffer.hpp"
#include "BinaryInputPackage.hpp"
#include "BinaryOutputPackage.hpp"

namespace Bt {
namespace Com {


template<typename ServerSocket, typename Socket>
class TcpServer 
{
   public:

      enum { TCP_SERVER_BUFFER_LENGHT = 32};
      enum { TCP_SERVER_CHECK_BYTE    = 0xAF};


      TcpServer(ServerSocket& iServerSocket, I_RequestServer& iHandler);
      ~TcpServer();
   
      virtual void workcycle();

   private:
   	  // Constructor to prohibit copy construction.
      TcpServer(const TcpServer&);

      // Operator= to prohibit copy assignment
      TcpServer& operator=(const TcpServer&);

      void waitForClient();
      void waitForRequest();
      void readSize();
      void readData();

      size_t calculateReadSize(size_t iAvailable);
      bool checkConnection();

      typedef void (TcpServer<ServerSocket,Socket>::*StateFunction)();

      ServerSocket* mServerSocket;
      Socket mSocket;
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

template<typename ServerSocket, typename Socket>
TcpServer<ServerSocket,Socket>::TcpServer(ServerSocket& iServerSocket, I_RequestServer& iHandler)
: mServerSocket(&iServerSocket), mStateFunction(&TcpServer<ServerSocket,Socket>::waitForClient), mHandler(&iHandler), mSize(0) , mInput(mInputBuffer), mOutput(mOutputBuffer) {

}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
TcpServer<ServerSocket,Socket>::~TcpServer() {

}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::workcycle(void) {
   (this->*mStateFunction)();
}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::waitForClient() {
   mSocket = mServerSocket->available();
   if (mSocket == true) {
      mStateFunction = &TcpServer<ServerSocket,Socket>::waitForRequest;
      workcycle();
   }
}


//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::waitForRequest() {
   if (mSocket.available() <= 0) {
      // Serial.println("w 0");
      checkConnection();
      return;
   }
   int checkByte = mSocket.read();
   // Serial.print("w c ");
   // Serial.println(checkByte,HEX);
   if (checkByte == -1) {
      checkConnection();
      return;
   }
   if (checkByte != TCP_SERVER_CHECK_BYTE) {
      Serial.print("wrong check byte ");
      Serial.print(checkByte,HEX);
      Serial.print(" != ");
      Serial.print(TCP_SERVER_CHECK_BYTE,HEX);
      Serial.println(" => close connection");
      mSocket.stop();
      mSocket = Socket();
      mStateFunction = &TcpServer<ServerSocket,Socket>::waitForClient;
      return;
   }
   mStateFunction = &TcpServer<ServerSocket,Socket>::readSize;
}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::readSize() {
   if (mSocket.available() <= 0) {
      // Serial.println("s 0");
      checkConnection();
      return;
   }
   int size = mSocket.read();
   // Serial.print("s s ");
   // Serial.println(size,HEX);
   if (size == -1) {
      checkConnection();
      return;
   }
   mSize = size;
   mInputBuffer.clear();
   mStateFunction = &TcpServer<ServerSocket,Socket>::readData;
}


//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::readData() {
   int available = mSocket.available();
   if (available <= 0) {
      // Serial.println("r 0");
      checkConnection();
      return;
   }

   // Serial.print("r a ");
   // Serial.println(available);
   size_t calculatedReadSize = calculateReadSize(available);
   // Serial.print("r c ");
   // Serial.println(calculatedReadSize);
   int read = mSocket.read(mInputBuffer.raw() + mInputBuffer.length(),calculatedReadSize);
   // Serial.print("r r ");
   // Serial.println(read);
   if (read == -1) {
      checkConnection();
      return;
   }

   mInputBuffer.filled(mInputBuffer.length() + read);

   if(mInputBuffer.length() < mSize) {
      return;
   }

   mOutputBuffer.clear();

   // Serial.println("h");
   mHandler->handleRequest(mInput,mOutput);

   if (mOutputBuffer.length() > 0) {

      // Serial.println("s c");
      mSocket.write(TCP_SERVER_CHECK_BYTE);

      // Serial.print("s l ");
      // Serial.println(mOutputBuffer.length());
      mSocket.write(mOutputBuffer.length());

      // Serial.println("s d");
      mSocket.write(mOutputBuffer.raw(),mOutputBuffer.length());

      if(mSocket.getWriteError()) {
         Serial.println("!!! WriteError !!!");
      }
   }


   mStateFunction = &TcpServer<ServerSocket,Socket>::waitForRequest;

}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
size_t TcpServer<ServerSocket,Socket>::calculateReadSize(size_t iAvailable) {
   size_t remaining = mSize - mInputBuffer.length();
   if (remaining < iAvailable) {
      return remaining;
   }
   return iAvailable;
}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
bool TcpServer<ServerSocket,Socket>::checkConnection() {
   if (!mSocket.connected()) {
      Serial.println("connection lost => restart socket");
      mSocket.flush();
      mSocket.stop();
      mSocket = Socket();
      mStateFunction = &TcpServer<ServerSocket,Socket>::waitForClient;
      return false;
   }
   return true;
}

//-------------------------------------------------------------------------------------------------


} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_TcpServer__hpp
