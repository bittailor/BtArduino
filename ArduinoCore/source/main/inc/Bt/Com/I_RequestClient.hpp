//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::I_RequestClient
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_I_RequestClient__hpp
#define INC__Bt_Com_I_RequestClient__hpp

#include "Bt/Com/I_InputPackage.hpp"
#include "Bt/Com/I_OutputPackage.hpp"

namespace Bt {
namespace Com {

class I_RequestClient {
   public:
      virtual ~I_RequestClient() {}
      
      virtual Com::I_OutputPackage& out() = 0;
      virtual Com::I_InputPackage& in() = 0;

      /**
       * Sends an action request.
       * An action request is a request without return value.
       */
      virtual void sendActionRequest() = 0;

      /**
       * Sends a function request.
       * An query request is a request with return value.
       */
      virtual void sendQueryRequest() = 0;
};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_I_RequestClient__hpp
