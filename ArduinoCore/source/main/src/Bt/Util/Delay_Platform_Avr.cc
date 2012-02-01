//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::Delay
//  
//*************************************************************************************************

#include <Arduino.h>

namespace Bt {
namespace Util {

//-------------------------------------------------------------------------------------------------

void delayInMilliseconds(unsigned int milliseconds) {
   delay(milliseconds);
}

//-------------------------------------------------------------------------------------------------

unsigned long microSeconds() {
   return micros();
}

//-------------------------------------------------------------------------------------------------

} // namespace Util
} // namespace Bt

