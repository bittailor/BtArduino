//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::InMemoryClientServer
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_InMemoryClientServer__hpp
#define INC__Bt_Com_InMemoryClientServer__hpp

#include "Bt/Com/I_RequestClient.hpp"
#include "Bt/Com/I_RequestServer.hpp"
#include "Bt/Com/StaticArrayPackageBuffer.hpp"
#include "Bt/Com/BinaryInputPackage.hpp"
#include "Bt/Com/BinaryOutputPackage.hpp"

namespace Bt {
namespace Com {

class InMemoryClientServer : public I_RequestClient
{

   public:
      enum {IN_MEMORY_BUFFER_LENGTH = 32 };

      InMemoryClientServer(I_RequestServer& iHandler);
      ~InMemoryClientServer();
   
      /** @see I_RequestClient::out() */
      virtual Com::I_OutputPackage& out();
      /** @see I_RequestClient::in() */
      virtual Com::I_InputPackage& in();
      /** @see I_RequestClient::sendActionRequest() */
      virtual void sendActionRequest();
      /** @see I_RequestClient::sendQueryRequest() */
      virtual void sendQueryRequest();

   private:
   	  // Constructor to prohibit copy construction.
      InMemoryClientServer(const InMemoryClientServer&);

      // Operator= to prohibit copy assignment
      InMemoryClientServer& operator=(const InMemoryClientServer&);

      I_RequestServer* mHandler;

      StaticArrayPackageBuffer<IN_MEMORY_BUFFER_LENGTH> mClientInputServerOuputBuffer;
      BinaryInputPackage mClientInput;
      BinaryOutputPackage mServerOuput;

      StaticArrayPackageBuffer<IN_MEMORY_BUFFER_LENGTH> mServerInputClientOuputBuffer;
      BinaryInputPackage mServerInput;
      BinaryOutputPackage mClientOuput;

};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_InMemoryClientServer__hpp
