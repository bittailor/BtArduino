//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::I_RequestHandler
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_I_RequestHandler__hpp
#define INC__Bt_Com_I_RequestHandler__hpp

#include "Bt/Com/I_InputPackage.hpp"
#include "Bt/Com/I_OutputPackage.hpp"

namespace Bt {
namespace Com {

class I_RequestHandler {
   public:
      virtual ~I_RequestHandler() {}
      
      virtual void handleRequest(Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut) = 0;
};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_I_RequestHandler__hpp
