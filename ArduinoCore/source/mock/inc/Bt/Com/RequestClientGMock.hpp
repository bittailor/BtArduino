//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::RequestClientGMock
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_RequestClientGMock__hpp
#define INC__Bt_Com_RequestClientGMock__hpp

#include <gmock/gmock.h>

#include "Bt/Com/I_RequestClient.hpp"

namespace Bt {
namespace Com {

class RequestClientGMock : public I_RequestClient {
   public:
      
      MOCK_METHOD0(out,Com::I_OutputPackage& ());
      MOCK_METHOD0(in,Com::I_InputPackage& ());
      MOCK_METHOD0(sendActionRequest,void());
      MOCK_METHOD0(sendQueryRequest,void());


};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_RequestClientGMock__hpp
