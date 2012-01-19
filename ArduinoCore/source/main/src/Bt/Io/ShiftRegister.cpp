//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Io::ShiftRegister
//  
//*************************************************************************************************

#include "Bt/Io/ShiftRegister.hpp"

#include <Arduino.h>

namespace Bt {
namespace Io {


//-------------------------------------------------------------------------------------------------

ShiftRegister::ShiftRegister(uint8_t iClockPin, uint8_t iLatchPin, uint8_t iDataPin)
: mClockPin(iClockPin), mLatchPin(iLatchPin), mDataPin(iDataPin) {
}

//-------------------------------------------------------------------------------------------------

ShiftRegister::~ShiftRegister() {

}

//-------------------------------------------------------------------------------------------------

void ShiftRegister::write(uint8_t iValue) {
   mLatchPin.off();
   shiftOutMsb(iValue);
   mLatchPin.on();
}

//-------------------------------------------------------------------------------------------------

void ShiftRegister::shiftOutMsb(uint8_t iValue) {
   /*
   for (uint8_t i = 0; i < 8; i++)  {
      mDataPin.set((iValue & (1 << (7 - i))));
      mClockPin.on();
      mClockPin.off();
   }
   */
   for (uint8_t i = 0 ; i < 8 ; i++)  {
      mDataPin.set(iValue & 0x80);
      iValue <<= 1;
      mClockPin.on();
      mClockPin.off();
   }

}

//-------------------------------------------------------------------------------------------------
} // namespace Io
} // namespace Bt
