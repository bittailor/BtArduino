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
#include "Bt/Workcycle/I_Runnable.hpp"
#include "Bt/Io/ShiftRegister.hpp"

namespace Bt {
namespace Com {


template<typename ServerSocket, typename Socket>
class TcpServer : public Workcycle::I_Runnable
{
   public:

      enum { TCP_SERVER_BUFFER_LENGHT = 32};
      enum { TCP_SERVER_START_REQUEST    = 0xAF};
      enum { TCP_SERVER_QUIT             = 0xAA};


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
      void sendData();

      bool checkReadSocket();
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
void TcpServer<ServerSocket,Socket>::workcycle() {
   (this->*mStateFunction)();
}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::waitForClient() {
   mSocket = mServerSocket->available();
   if (mSocket) {
      mStateFunction = &TcpServer<ServerSocket,Socket>::waitForRequest;
   }
}


//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::waitForRequest() {
   if (!checkReadSocket()) {
      return;
   }

   int commandByte = mSocket.read();

   if (commandByte == -1) {
      checkConnection();
      return;
   }

   if (commandByte == TCP_SERVER_START_REQUEST) {
      mStateFunction = &TcpServer<ServerSocket,Socket>::readSize;
      return;
   }

   if (commandByte == TCP_SERVER_QUIT) {
      mSocket.stop();
      mSocket = Socket();
      mStateFunction = &TcpServer<ServerSocket,Socket>::waitForClient;
      return;
   }

}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::readSize() {
   if (!checkReadSocket()) {
      return;
   }

   int size = mSocket.read();
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
   if (!checkReadSocket()) {
      return;
   }

   int data = mSocket.read();
   if (data == -1) {
      checkConnection();
      return;
   }

   mInputBuffer.put(data);

   if(mInputBuffer.length() < mSize) {
      return;
   }

   mOutputBuffer.clear();

   mHandler->handleRequest(mInput,mOutput);

   if (mOutputBuffer.length() > 0) {
      mStateFunction = &TcpServer<ServerSocket,Socket>::sendData;
      return;
   }

   mStateFunction = &TcpServer<ServerSocket,Socket>::waitForRequest;

}
//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::sendData() {

   mSocket.write(TCP_SERVER_START_REQUEST);
   mSocket.write(mOutputBuffer.length());
   mSocket.write(mOutputBuffer.raw(),mOutputBuffer.length());

   mStateFunction = &TcpServer<ServerSocket,Socket>::waitForRequest;

}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
bool TcpServer<ServerSocket,Socket>::checkConnection() {
   if (!mSocket.connected()) {
      mSocket.flush();
      mSocket.stop();
      mSocket = Socket();
      mStateFunction = &TcpServer<ServerSocket,Socket>::waitForClient;
      return false;
   }
   return true;
}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
bool TcpServer<ServerSocket,Socket>::checkReadSocket() {
   if (!mSocket.connected()) {
      mSocket.flush();
      mSocket.stop();
      mSocket = Socket();
      mStateFunction = &TcpServer<ServerSocket,Socket>::waitForClient;
      return false;
   }
   int available = mSocket.available();
   if (available <= 0) {
      return false;
   }

   return true;
}

//-------------------------------------------------------------------------------------------------


} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_TcpServer__hpp
