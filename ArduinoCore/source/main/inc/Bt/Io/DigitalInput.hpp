//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Io::DigitalInput
//  
//*************************************************************************************************

#ifndef INC__Bt_Io_DigitalInput__hpp
#define INC__Bt_Io_DigitalInput__hpp

#include <Bt/Workcycle/I_Runnable.hpp>

#include "I_DigitalInput.hpp"
#include "I_RawInput.hpp"


namespace Bt {
namespace Io {

class DigitalInput : public I_DigitalInput, public Bt::Workcycle::I_Runnable
{
   public:
      DigitalInput(I_RawInput<bool>& iRawInput);
      ~DigitalInput();

      virtual I_DigitalInput& read();
      virtual bool value();

      virtual void add(I_DigitalInputListener& iListener);
      virtual void remove(I_DigitalInputListener& iListener);

      virtual void workcycle();
   
   private:
   	  // Constructor to prohibit copy construction.
      DigitalInput(const DigitalInput&);

      // Operator= to prohibit copy assignment
      DigitalInput& operator=(const DigitalInput&);

      void notify();

      typedef Util::IntrusiveList<I_DigitalInputListener> Listeners;

      I_RawInput<bool>* mRawInput;
      bool mValue;
      Listeners mListeners;
};

} // namespace Io
} // namespace Bt

#endif // INC__Bt_Io_DigitalInput__hpp
