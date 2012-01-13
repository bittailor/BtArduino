//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::TcpServer
//  
//*************************************************************************************************

#include "Bt/Com/TcpServer.hpp"

namespace Bt {
namespace Com {

//-------------------------------------------------------------------------------------------------

TcpServer::TcpServer(EthernetServer& iServerSocket, I_RequestServer& iHandler)
: mServerSocket(&iServerSocket), mStateFunction(&TcpServer::waitForRequest), mHandler(&iHandler), mSize(0) , mInput(mInputBuffer), mOutput(mOutputBuffer) {

}

//-------------------------------------------------------------------------------------------------

TcpServer::~TcpServer() {

}

//-------------------------------------------------------------------------------------------------

void TcpServer::workcycle(void) {
   (this->*mStateFunction)();
}

//-------------------------------------------------------------------------------------------------

void TcpServer::waitForClient() {
   mSocket = mServerSocket->available();
   if (mSocket == true) {
      mStateFunction = &TcpServer::waitForRequest;
      workcycle();
   }
}


//-------------------------------------------------------------------------------------------------

void TcpServer::waitForRequest() {
   if (mSocket.available() <= 0) {
      checkConnection();
      return;
   }

   uint8_t checkByte = mSocket.read();

   if (checkByte != TCP_SERVER_CHECK_BYTE) {
      mSocket.stop();
      mStateFunction = &TcpServer::waitForClient;
      return;
   }

   mStateFunction = &TcpServer::readSize;
   workcycle();

}

//-------------------------------------------------------------------------------------------------

void TcpServer::readSize() {


   if (mSocket.available() <= 0) {
      checkConnection();
      return;
   }

   mSize = mSocket.read();
   mInputBuffer.clear();
   mStateFunction = &TcpServer::readData;
   workcycle();
}


//-------------------------------------------------------------------------------------------------

void TcpServer::readData() {
   int available = mSocket.available();
   if (available <= 0) {
      checkConnection();
      return;
   }

   size_t read = mSocket.read(mInputBuffer.raw() + mInputBuffer.length(),calculateReadSize(available));
   mInputBuffer.filled(mInputBuffer.length() + read);

   if(mInputBuffer.length() < mSize) {
      return;
   }

   mOutputBuffer.clear();

   mHandler->handleRequest(mInput,mOutput);

   mSocket.write(TCP_SERVER_CHECK_BYTE);
   mSocket.write(mOutputBuffer.length());
   mSocket.write(mOutputBuffer.raw(),mOutputBuffer.length());

   mStateFunction = &TcpServer::waitForRequest;

}

//-------------------------------------------------------------------------------------------------

size_t TcpServer::calculateReadSize(size_t iAvailable) {
   size_t remaining = mSize - mInputBuffer.length();
   if (remaining < iAvailable) {
      return remaining;
   }
   return iAvailable;
}

//-------------------------------------------------------------------------------------------------

bool TcpServer::checkConnection() {
   if (!mSocket.connected()) {
      mStateFunction = &TcpServer::waitForClient;
      return false;
   }
   return true;
}

//-------------------------------------------------------------------------------------------------

} // namespace Com
} // namespace Bt
