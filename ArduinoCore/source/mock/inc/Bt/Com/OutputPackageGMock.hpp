//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::OutputPackageGMock
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_OutputPackageGMock__hpp
#define INC__Bt_Com_OutputPackageGMock__hpp

#include <gmock/gmock.h>

#include "Bt/Com/I_OutputPackage.hpp"

namespace Bt {
namespace Com {

class OutputPackageGMock : public I_OutputPackage {
   public:
      
     MOCK_METHOD0(buffer, I_PackageBuffer& ());

     MOCK_METHOD1(write,I_OutputPackage& (bool oValue));
     MOCK_METHOD1(write,I_OutputPackage& (int8_t oValue));
     MOCK_METHOD1(write,I_OutputPackage& (uint8_t oValue));

};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_OutputPackageGMock__hpp
