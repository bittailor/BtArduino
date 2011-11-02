//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::BinaryInputPackage
//  
//*************************************************************************************************

#include <stdio.h>

#include "Bt/Com/BinaryInputPackage.hpp"

namespace Bt {
namespace Com {


//-------------------------------------------------------------------------------------------------

BinaryInputPackage::BinaryInputPackage(I_PackageBuffer& iBuffer)
: mBuffer(&iBuffer){

}

//-------------------------------------------------------------------------------------------------

BinaryInputPackage::~BinaryInputPackage() {

}

//-------------------------------------------------------------------------------------------------

I_InputPackage& BinaryInputPackage::operator>>(bool& oValue) {
   int16_t value = mBuffer->get();
   if (value != EOF) {
      if (value == 0) {
         oValue = false;

      } else {
         oValue = true;
      }
   }
   return *this;
}

//-------------------------------------------------------------------------------------------------

I_InputPackage& BinaryInputPackage::operator>>(int8_t& oValue) {
   int16_t value = mBuffer->get();
   if (value != EOF) {
      oValue = static_cast<int8_t>(value);
   }
   return *this;
}

//-------------------------------------------------------------------------------------------------

I_InputPackage& BinaryInputPackage::operator>>(uint8_t& oValue) {
   int16_t value = mBuffer->get();
   if (value != EOF) {
      oValue = value;
   }
   return *this;
}

//-------------------------------------------------------------------------------------------------

} // namespace Com
} // namespace Bt
