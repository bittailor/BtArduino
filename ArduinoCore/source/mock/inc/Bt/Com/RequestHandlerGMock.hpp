//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::RequestHandlerGMock
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_RequestHandlerGMock__hpp
#define INC__Bt_Com_RequestHandlerGMock__hpp

#include <gmock/gmock.h>

#include "Bt/Com/I_RequestHandler.hpp"

namespace Bt {
namespace Com {

class RequestHandlerGMock : public I_RequestHandler {
   public:
      MOCK_METHOD2(handleRequest,void (Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut));
};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_RequestHandlerGMock__hpp
