//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::InMemoryClientServer
//  
//*************************************************************************************************

#include "Bt/Com/InMemoryClientServer.hpp"

namespace Bt {
namespace Com {


//-------------------------------------------------------------------------------------------------

InMemoryClientServer::InMemoryClientServer(I_RequestServer& iHandler)
: mHandler(&iHandler)
, mClientInput(mClientInputServerOuputBuffer), mServerOuput(mClientInputServerOuputBuffer)
, mServerInput(mServerInputClientOuputBuffer), mClientOuput(mServerInputClientOuputBuffer) {

}

//-------------------------------------------------------------------------------------------------

InMemoryClientServer::~InMemoryClientServer() {

}

//-------------------------------------------------------------------------------------------------

Com::I_OutputPackage& InMemoryClientServer::out() {
   return mClientOuput;
}

//-------------------------------------------------------------------------------------------------

Com::I_InputPackage& InMemoryClientServer::in() {
   return mClientInput;
}

//-------------------------------------------------------------------------------------------------

void InMemoryClientServer::sendActionRequest() {
   mClientInputServerOuputBuffer.clear();
   mHandler->handleRequest(mServerInput,mServerOuput);
   mServerInputClientOuputBuffer.clear();
   mClientInputServerOuputBuffer.clear(); // ActionRequst does not have an answer !
}

//-------------------------------------------------------------------------------------------------

void InMemoryClientServer::sendQueryRequest() {
   mClientInputServerOuputBuffer.clear();
   mHandler->handleRequest(mServerInput,mServerOuput);
   mServerInputClientOuputBuffer.clear();

}

//-------------------------------------------------------------------------------------------------

} // namespace Com
} // namespace Bt
