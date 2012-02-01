//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::Time
//  
//*************************************************************************************************

#include "Bt/Util/Time.hpp"
#include "Bt/Util/Delay.hpp"

namespace Bt {
namespace Util {


//-------------------------------------------------------------------------------------------------

Time::Time() {

}

//-------------------------------------------------------------------------------------------------

Time::~Time() {

}

//-------------------------------------------------------------------------------------------------

unsigned long Time::microSeconds() {
   return Bt::Util::microSeconds();
}

//-------------------------------------------------------------------------------------------------

} // namespace Util
} // namespace Bt