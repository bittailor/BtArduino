//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Io::ShiftRegister
//  
//*************************************************************************************************

#ifndef INC__Bt_Io_ShiftRegister__hpp
#define INC__Bt_Io_ShiftRegister__hpp

#include <stdint.h>

#include "Bt/Io/DigitalOutput.hpp"

namespace Bt {
namespace Io {

class ShiftRegister 
{
   public:
      ShiftRegister(uint8_t iClockPin, uint8_t iLatchPin, uint8_t iDataPin);
      ~ShiftRegister();

      void write(uint8_t iValue);
   
   private:
   	  // Constructor to prohibit copy construction.
      ShiftRegister(const ShiftRegister&);

      // Operator= to prohibit copy assignment
      ShiftRegister& operator=(const ShiftRegister&);

      void shiftOutMsb(uint8_t iValue);

      DigitalOutput mClockPin;
      DigitalOutput mLatchPin;
      DigitalOutput mDataPin;

};

} // namespace Io
} // namespace Bt

#endif // INC__Bt_Io_ShiftRegister__hpp
