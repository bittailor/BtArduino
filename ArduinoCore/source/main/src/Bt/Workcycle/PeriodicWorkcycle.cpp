//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Workcycle::PeriodicWorkcycle
//  
//*************************************************************************************************

#include "Bt/Workcycle/PeriodicWorkcycle.hpp"

#include <Arduino.h>

namespace Bt {
namespace Workcycle {


//-------------------------------------------------------------------------------------------------

PeriodicWorkcycle::PeriodicWorkcycle(unsigned long iPeriodInMicroSeconds, Util::I_Time& iTime)
: mTime(&iTime), mPeriodInMicroSeconds(iPeriodInMicroSeconds), mNextWorkcycle(0){
}

//-------------------------------------------------------------------------------------------------

PeriodicWorkcycle::~PeriodicWorkcycle() {

}

//-------------------------------------------------------------------------------------------------

void PeriodicWorkcycle::workcycle() {
   unsigned long now = mTime->microSeconds();
   if (now >= mNextWorkcycle) {
      // mNextWorkcycle = now + mPeriodInMicroSeconds;
      while(now >= mNextWorkcycle) {
         mNextWorkcycle += mPeriodInMicroSeconds;
      }
      oneWorkcycle();
   }
}

//-------------------------------------------------------------------------------------------------

} // namespace Workcycle
} // namespace Bt
