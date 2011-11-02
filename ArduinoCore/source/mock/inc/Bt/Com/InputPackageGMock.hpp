//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::InputPackageGMock
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_InputPackageGMock__hpp
#define INC__Bt_Com_InputPackageGMock__hpp

#include <gmock/gmock.h>

#include "Bt/Com/I_InputPackage.hpp"

namespace Bt {
namespace Com {

class InputPackageGMock : public I_InputPackage {
   public:
      
      virtual I_InputPackage& operator>>(bool& oValue) {return stream(oValue);}
      virtual I_InputPackage& operator>>(int8_t& oValue) {return stream(oValue);}
      virtual I_InputPackage& operator>>(uint8_t& oValue) {return stream(oValue);}

      MOCK_METHOD1(stream,I_InputPackage& (bool& oValue));
      MOCK_METHOD1(stream,I_InputPackage& (int8_t& oValue));
      MOCK_METHOD1(stream,I_InputPackage& (uint8_t& oValue));
};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_InputPackageGMock__hpp
