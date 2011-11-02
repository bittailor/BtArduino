//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::BinaryOutputPackage
//  
//*************************************************************************************************

#include "Bt/Com/BinaryOutputPackage.hpp"

namespace Bt {
namespace Com {


//-------------------------------------------------------------------------------------------------

BinaryOutputPackage::BinaryOutputPackage(I_PackageBuffer& iBuffer)
: mBuffer(&iBuffer){

}

//-------------------------------------------------------------------------------------------------

BinaryOutputPackage::~BinaryOutputPackage() {

}

//-------------------------------------------------------------------------------------------------

I_OutputPackage& BinaryOutputPackage::operator<<(bool iValue) {
   uint8_t value = iValue ? 1 : 0;
   mBuffer->put(value);
   return *this;
}

//-------------------------------------------------------------------------------------------------

I_OutputPackage& BinaryOutputPackage::operator<<(int8_t iValue) {
   mBuffer->put(static_cast<uint8_t>(iValue));
   return *this;
}

//-------------------------------------------------------------------------------------------------

I_OutputPackage& BinaryOutputPackage::operator<<(uint8_t iValue) {
   mBuffer->put(iValue);
   return *this;
}

//-------------------------------------------------------------------------------------------------

} // namespace Com
} // namespace Bt
