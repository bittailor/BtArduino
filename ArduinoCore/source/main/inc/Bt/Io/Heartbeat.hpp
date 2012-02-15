//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Io::Heartbeat
//  
//*************************************************************************************************

#ifndef INC__Bt_Io_Heartbeat__hpp
#define INC__Bt_Io_Heartbeat__hpp

#include "Bt/Workcycle/I_Runnable.hpp"
#include "DigitalOutput.hpp"

namespace Bt {
namespace Io {

class Heartbeat : public Bt::Workcycle::I_Runnable
{
   public:
      Heartbeat(uint8_t iOutputPin);
      ~Heartbeat();

      virtual void workcycle();

   private:
      Bt::Io::DigitalOutput mOutput;
};

} // namespace Io
} // namespace Bt

#endif // INC__Bt_Io_Heartbeat__hpp
