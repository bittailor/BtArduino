//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Io::CapacitiveSensorInput
//  
//*************************************************************************************************

#include "Bt/Io/CapacitiveSensorInput.hpp"

namespace Bt {
namespace Io {


//-------------------------------------------------------------------------------------------------

CapacitiveSensorInput::CapacitiveSensorInput(uint8_t iSendPin,
                                             uint8_t iReceivePin,
                                             long iHighThreshold,
                                             long iLowThreshold)
: mSensor(iSendPin,iReceivePin), mHighThreshold(iHighThreshold), mLowThreshold(iLowThreshold), mValue(false) {

}

//-------------------------------------------------------------------------------------------------

CapacitiveSensorInput::~CapacitiveSensorInput() {

}

//-------------------------------------------------------------------------------------------------

bool CapacitiveSensorInput::read() {
   long capacitance = mSensor.capacitiveSensor(30);
   if (mValue) {
      if (capacitance < mLowThreshold) {
         mValue = false;
      }
   } else {
      if (capacitance > mHighThreshold) {
            mValue = true;
      }
   }
   return mValue;
}

//-------------------------------------------------------------------------------------------------


} // namespace Io
} // namespace Bt
