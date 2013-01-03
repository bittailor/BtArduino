//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Io::I_DigitalInputListener
//  
//*************************************************************************************************

#ifndef INC__Bt_Io_I_DigitalInputListener__hpp
#define INC__Bt_Io_I_DigitalInputListener__hpp

#include <Bt/Util/IntrusiveList.hpp>

namespace Bt {
namespace Io {

class I_DigitalInputListener : public Util::IntrusiveList<I_DigitalInputListener>::Element {
   public:
      virtual ~I_DigitalInputListener() {}
      
      virtual void high() = 0;
      virtual void low() = 0;
};

} // namespace Io
} // namespace Bt

#endif // INC__Bt_Io_I_DigitalInputListener__hpp
