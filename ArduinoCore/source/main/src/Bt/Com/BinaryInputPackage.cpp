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

I_PackageBuffer& BinaryInputPackage::buffer() {
   return *mBuffer;
}

//-------------------------------------------------------------------------------------------------

bool BinaryInputPackage::readBool() {
   int16_t value = mBuffer->get();
   if (value != EOF) {
      if (value == 0) {
         return false;

      } else {
         return true;
      }
   }
   return false;
}

//-------------------------------------------------------------------------------------------------

int8_t BinaryInputPackage::readInt8() {
   int16_t value = mBuffer->get();
   if (value != EOF) {
      return static_cast<int8_t>(value);
   }
   return 0;
}

//-------------------------------------------------------------------------------------------------

uint8_t BinaryInputPackage::readUInt8() {
   int16_t value = mBuffer->get();
   if (value != EOF) {
      return value;
   }
   return 0;
}

//-------------------------------------------------------------------------------------------------

} // namespace Com
} // namespace Bt
