//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Io::CapacitiveSensorInput
//  
//*************************************************************************************************

#ifndef INC__Bt_Io_CapacitiveSensorInput__hpp
#define INC__Bt_Io_CapacitiveSensorInput__hpp

#include "I_RawInput.hpp"
#include "CapacitiveSensor.hpp"

namespace Bt {
namespace Io {

class CapacitiveSensorInput : public I_RawInput<bool>
{
   public:

      CapacitiveSensorInput(uint8_t iSendPin,
                            uint8_t iReceivePin,
                            long iHighThreshold,
                            long iLowThreshold,
                            uint8_t iReadSamples = 255);
      ~CapacitiveSensorInput();

      virtual bool read();
   
   private:
   	  // Constructor to prohibit copy construction.
      CapacitiveSensorInput(const CapacitiveSensorInput&);

      // Operator= to prohibit copy assignment
      CapacitiveSensorInput& operator=(const CapacitiveSensorInput&);

      CapacitiveSensor mSensor;
      const long mHighThreshold;
      const long mLowThreshold;
      bool mValue;
      uint8_t mReadSamples;
};

} // namespace Io
} // namespace Bt

#endif // INC__Bt_Io_CapacitiveSensorInput__hpp
