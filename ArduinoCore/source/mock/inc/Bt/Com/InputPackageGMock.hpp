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
      
      MOCK_METHOD0(buffer, I_PackageBuffer& ());

      MOCK_METHOD0(readBool, bool ());
      MOCK_METHOD0(readInt8, int8_t ());
      MOCK_METHOD0(readUInt8, uint8_t ());

};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_InputPackageGMock__hpp
