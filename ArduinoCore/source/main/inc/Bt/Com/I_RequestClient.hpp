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
      
      virtual void sendRequest(Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut) = 0;
};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_I_RequestClient__hpp
