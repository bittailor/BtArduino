//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::TwoWireServer
//  
//*************************************************************************************************

#include "Bt/Com/TwoWireServer.hpp"
#include "Bt/Com/TwoWireClient.hpp"

namespace Bt {
namespace Com {

/*
//-------------------------------------------------------------------------------------------------

TwoWireServer* TwoWireServer::sInstance = 0;

//-------------------------------------------------------------------------------------------------

void TwoWireServer::onRequestService(void) {
   if (sInstance != 0) {
      sInstance->request();
   }
}

//-------------------------------------------------------------------------------------------------

void TwoWireServer::onReceiveService(uint8_t* iData, int iNumberOfBytes) {
   if (sInstance != 0) {
      sInstance->receive(iData,iNumberOfBytes);
   }
}

//-------------------------------------------------------------------------------------------------

TwoWireServer::TwoWireServer(uint8_t address, I_RequestServer& iHandler)
:mInput(mInputBuffer), mOutput(mOutputBuffer), mHandler(&iHandler) {
   if (sInstance == 0) {
      twi_setAddress(address);
      twi_attachSlaveTxEvent(&TwoWireServer::onRequestService);
      twi_attachSlaveRxEvent(&TwoWireServer::onReceiveService);
      twi_init();
   }
   // TODO what should we do in the error case ?
}

//-------------------------------------------------------------------------------------------------

TwoWireServer::~TwoWireServer() {

}

//-------------------------------------------------------------------------------------------------

void TwoWireServer::request(void) {
   if(twi_transmit(mOutputBuffer.raw(), mOutputBuffer.length()) == 0) ;
   {
      mOutputBuffer.clear();
   }
}

//-------------------------------------------------------------------------------------------------

void TwoWireServer::receive(uint8_t* iData, int iNumberOfBytes ) {
   mOutputBuffer.clear();
   mInputBuffer.clear();
   for (int i = 0; i < iNumberOfBytes; ++i) {
      mInputBuffer.put(iData[i]);
   }

   mHandler->handleRequest(mInput,mOutput);
}

//-------------------------------------------------------------------------------------------------
*/


} // namespace Com
} // namespace Bt
