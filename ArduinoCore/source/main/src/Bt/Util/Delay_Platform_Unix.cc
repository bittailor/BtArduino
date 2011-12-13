//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::Delay
//  
//*************************************************************************************************

#include <unistd.h>

namespace Bt {
namespace Util {

void delayInMilliseconds(unsigned int milliseconds) {
   sleep(milliseconds);
}

} // namespace Util
} // namespace Bt

