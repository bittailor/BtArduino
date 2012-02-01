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

namespace Bt {
namespace Com {


template<typename ServerSocket, typename Socket>
class TcpServer : public Workcycle::I_Runnable
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
      bool checkConnection(Socket iSocket);
      void checkStateFunction();

      typedef void (TcpServer<ServerSocket,Socket>::*StateFunction)();

      ServerSocket* mServerSocket;
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
   checkStateFunction();
   (this->*mStateFunction)();
}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::checkStateFunction() {
   if (mStateFunction == &TcpServer<ServerSocket,Socket>::waitForClient  ) return;
   if (mStateFunction == &TcpServer<ServerSocket,Socket>::waitForRequest ) return;
   if (mStateFunction == &TcpServer<ServerSocket,Socket>::readSize       ) return;
   if (mStateFunction == &TcpServer<ServerSocket,Socket>::readData       ) return;

   Serial.print("!!! wrong state function !!!");

   delay(1000);

   mStateFunction = &TcpServer<ServerSocket,Socket>::waitForRequest;

}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::waitForClient() {
   Socket socket = mServerSocket->available();
   if (socket == true) {
      mStateFunction = &TcpServer<ServerSocket,Socket>::waitForRequest;
   }
}


//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::waitForRequest() {
   Socket socket = mServerSocket->available();
   if (socket != true) {
      return;
   }

   if (socket.available() <= 0) {
      // Serial.println("w 0");
      checkConnection(socket);
      return;
   }
   int checkByte = socket.read();
   // Serial.print("w c ");
   // Serial.println(checkByte,HEX);
   if (checkByte == -1) {
      checkConnection(socket);
      return;
   }
   if (checkByte != TCP_SERVER_CHECK_BYTE) {
      Serial.print("wrong check byte ");
      Serial.print(checkByte,HEX);
      Serial.print(" != ");
      Serial.print(TCP_SERVER_CHECK_BYTE,HEX);
      Serial.println(" => close connection");
      socket.stop();
      mStateFunction = &TcpServer<ServerSocket,Socket>::waitForClient;
      return;
   }
   mStateFunction = &TcpServer<ServerSocket,Socket>::readSize;
}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::readSize() {
   Socket socket = mServerSocket->available();
   if (socket != true) {
      return;
   }

   if (socket.available() <= 0) {
      // Serial.println("s 0");
      checkConnection(socket);
      return;
   }
   int size = socket.read();
   // Serial.print("s s ");
   // Serial.println(size,HEX);
   if (size == -1) {
      checkConnection(socket);
      return;
   }
   mSize = size;
   mInputBuffer.clear();
   mStateFunction = &TcpServer<ServerSocket,Socket>::readData;
}


//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::readData() {
   Socket socket = mServerSocket->available();
   if (socket != true) {
      return;
   }

   if (socket.available() <= 0) {
      // Serial.println("r 0");
      checkConnection(socket);
      return;
   }

   int data = socket.read();
   if (data == -1) {
      checkConnection(socket);
      return;
   }

   mInputBuffer.put(data);
   if(mInputBuffer.length() < mSize) {
      return;
   }

   mOutputBuffer.clear();

   // Serial.println("h");
   mHandler->handleRequest(mInput,mOutput);

   if (mOutputBuffer.length() > 0) {

      // Serial.println("s c");
      socket.write(TCP_SERVER_CHECK_BYTE);

      // Serial.print("s l ");
      // Serial.println(mOutputBuffer.length());
      socket.write(mOutputBuffer.length());

      // Serial.println("s d");
      socket.write(mOutputBuffer.raw(),mOutputBuffer.length());

      if(socket.getWriteError()) {
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
bool TcpServer<ServerSocket,Socket>::checkConnection(Socket iSocket) {
   if (!iSocket.connected()) {
      Serial.println("connection lost => restart socket");
      iSocket.flush();
      iSocket.stop();
      iSocket = Socket();
      mStateFunction = &TcpServer<ServerSocket,Socket>::waitForClient;
      return false;
   }
   return true;
}

//-------------------------------------------------------------------------------------------------


} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_TcpServer__hpp
