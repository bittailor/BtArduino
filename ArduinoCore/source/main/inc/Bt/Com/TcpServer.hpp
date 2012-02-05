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
      enum { TCP_SERVER_CHECK_BYTE    = 0xAF};


      TcpServer(ServerSocket& iServerSocket);
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

      bool checkReadSocket();
      bool checkConnection(Socket iSocket);
      void checkStateFunction();

      typedef void (TcpServer<ServerSocket,Socket>::*StateFunction)();


      ServerSocket* mServerSocket;
      Socket mSocket;
      StateFunction mStateFunction;
      size_t mSize;
      Bt::Io::ShiftRegister mShift;

};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
TcpServer<ServerSocket,Socket>::TcpServer(ServerSocket& iServerSocket)
: mServerSocket(&iServerSocket), mStateFunction(&TcpServer<ServerSocket,Socket>::waitForClient), mSize(0), mShift(5,6,7) {
   for (int i = 0; i < 256 ; ++i) {
      mShift.write(i);
      delay(10);
   }
   mShift.write(0);
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

   delay(1000);

   mStateFunction = &TcpServer<ServerSocket,Socket>::waitForRequest;

}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::waitForClient() {
   mSocket = mServerSocket->available();
   if (mSocket == true) {
      mStateFunction = &TcpServer<ServerSocket,Socket>::waitForRequest;
   }
}


//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::waitForRequest() {
   if (!checkReadSocket()) {
      return;
   }

   int checkByte = mSocket.read();
   if (checkByte == -1) {
      checkConnection(mSocket);
      return;
   }
   if (checkByte != TCP_SERVER_CHECK_BYTE) {
      mSocket.stop();
      mStateFunction = &TcpServer<ServerSocket,Socket>::waitForClient;
      return;
   }
   mStateFunction = &TcpServer<ServerSocket,Socket>::readSize;
}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
void TcpServer<ServerSocket,Socket>::readSize() {
   if (!checkReadSocket()) {
      return;
   }

   int size = mSocket.read();
   if (size == -1) {
      checkConnection(mSocket);
      return;
   }
   mSize = size;
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
      checkConnection(mSocket);
      return;
   }

   mShift.write(data);
   mSize--;
   if(mSize > 0) {
      return;
   }

   mStateFunction = &TcpServer<ServerSocket,Socket>::waitForRequest;

}

//-------------------------------------------------------------------------------------------------

template<typename ServerSocket, typename Socket>
bool TcpServer<ServerSocket,Socket>::checkConnection(Socket iSocket) {
   if (!iSocket.connected()) {
      iSocket.flush();
      iSocket.stop();
      iSocket = Socket();
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
