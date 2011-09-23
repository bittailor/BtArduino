//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//  
//-------------------------------------------------------------------------------------------------
//
//  Bt::Io::DigitalOutput
//
//*************************************************************************************************

#include "Bt/Io/DigitalOutput.hpp"

#include <avr/interrupt.h>

#include "pins_arduino.h"
#include "wiring.h"

namespace Bt {
namespace Io {


//-------------------------------------------------------------------------------------------------

DigitalOutput::DigitalOutput(uint8_t iPin)
: mPin(iPin)
, mBit(digitalPinToBitMask(iPin))
, mOut(0)
, mMirror(false)
{

   pinMode(iPin,OUTPUT);

   uint8_t timer = digitalPinToTimer(iPin);
   uint8_t port = digitalPinToPort(iPin);
   if (port == NOT_A_PIN)
   {
      return;
   }

   // If the pin that support PWM output, we need to turn it off
   // before doing a digital write.
   if (timer != NOT_ON_TIMER)
   {
      turnOffPWM(timer);
   }

   mOut = portOutputRegister(port);
}

//-------------------------------------------------------------------------------------------------

DigitalOutput::~DigitalOutput()
{

}

//-------------------------------------------------------------------------------------------------

void DigitalOutput::set(bool iValue)
{

   mMirror = iValue;
   if (!iValue) {
      uint8_t oldSREG = SREG;
      cli();
      *mOut &= ~mBit;
      SREG = oldSREG;
   } else {
      uint8_t oldSREG = SREG;
      cli();
      *mOut |= mBit;
      SREG = oldSREG;
   }
}

//-------------------------------------------------------------------------------------------------

} // namespace Io
} // namespace Bt
