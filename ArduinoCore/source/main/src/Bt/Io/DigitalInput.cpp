//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Io::DigitalInput
//  
//*************************************************************************************************

#include "Bt/Io/DigitalInput.hpp"

namespace Bt {
namespace Io {


//-------------------------------------------------------------------------------------------------

DigitalInput::DigitalInput(I_RawInput<bool>& iRawInput) : mRawInput(&iRawInput), mValue(false) {

}

//-------------------------------------------------------------------------------------------------

DigitalInput::~DigitalInput() {

}

//-------------------------------------------------------------------------------------------------

I_DigitalInput& DigitalInput::read() {
   bool value = mRawInput->read();
   if (mValue != value) {
      mValue = value;
      notify();
   }
   return *this;
}

//-------------------------------------------------------------------------------------------------

bool DigitalInput::value(){
   return mValue;
}

//-------------------------------------------------------------------------------------------------


void DigitalInput::add(I_DigitalInputListener& iListener) {
   mListeners.pushBack(iListener);
}

//-------------------------------------------------------------------------------------------------

void DigitalInput::remove(I_DigitalInputListener& iListener) {
   mListeners.remove(iListener);
}


//-------------------------------------------------------------------------------------------------

void DigitalInput::workcycle() {
   read();
}

//-------------------------------------------------------------------------------------------------

void DigitalInput::notify() {
   for (Listeners::Iterator iterator = mListeners.begin(), end = mListeners.end(); iterator != end; ++iterator) {
      if (mValue) {
         iterator->high();
      } else {
         iterator->low();
      }
   }
}

//-------------------------------------------------------------------------------------------------

} // namespace Io
} // namespace Bt
