//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore     
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Io::DigitalOutput
//
//*************************************************************************************************

#ifndef INC__Bt_Io_DigitalOutput__hpp
#define INC__Bt_Io_DigitalOutput__hpp

#include <stdint.h>

namespace Bt {
namespace Io {

class DigitalOutput 
{
   public:
      DigitalOutput(uint8_t iPin);
      ~DigitalOutput();

      void on();
      void off();
      void toggle();
      void set(bool iValue);

      bool isOn();

   private:
        // Constructor to prohibit copy construction.
      DigitalOutput(const DigitalOutput&);

      // Operator= to prohibit copy assignment
      DigitalOutput& operator=(const DigitalOutput&);

      uint8_t mPin;
      uint8_t mBit;
      volatile uint8_t* mOut;
      bool mMirror;
};

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

inline void DigitalOutput::on()
{
   set(true);
}

//-------------------------------------------------------------------------------------------------

inline void DigitalOutput::off()
{
   set(false);
}

//-------------------------------------------------------------------------------------------------

inline void DigitalOutput::toggle()
{
   set(!mMirror);
}

//-------------------------------------------------------------------------------------------------

inline bool DigitalOutput::isOn()
{
   return mMirror;
}

//-------------------------------------------------------------------------------------------------

} // namespace Io
} // namespace Bt

#endif // INC__Bt_Io_DigitalOutput__hpp
