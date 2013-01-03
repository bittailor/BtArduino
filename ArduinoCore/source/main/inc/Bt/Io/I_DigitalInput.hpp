//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Io::I_DigitalInput
//  
//*************************************************************************************************

#ifndef INC__Bt_Io_I_DigitalInput__hpp
#define INC__Bt_Io_I_DigitalInput__hpp

#include "I_DigitalInputListener.hpp"

namespace Bt {
namespace Io {

class I_DigitalInput {
   public:
      virtual ~I_DigitalInput() {}

      virtual I_DigitalInput& read() = 0;
      virtual bool value() = 0;

      virtual void add(I_DigitalInputListener& iListener) = 0;
      virtual void remove(I_DigitalInputListener& iListener) = 0;
};

} // namespace Io
} // namespace Bt

#endif // INC__Bt_Io_I_DigitalInput__hpp
