//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Io::DigitalInputListener
//  
//*************************************************************************************************

#ifndef INC__Bt_Io_DigitalInputListener__hpp
#define INC__Bt_Io_DigitalInputListener__hpp

namespace Bt {
namespace Io {

template<typename T>
class DigitalInputListener : public I_DigitalInputListener {
   public:
      typedef void (T::*MemberFunction)(bool);

      DigitalInputListener(T& iObject, MemberFunction iMemberFunction)
      : mObject(&iObject), mMemberFunction(iMemberFunction) {
      }

      virtual void high() {
         (mObject->*mMemberFunction)(true);
      }

      virtual void low() {
         (mObject->*mMemberFunction)(false);
      }

   private:
      T* mObject;
      MemberFunction mMemberFunction;
};

} // namespace Io
} // namespace Bt

#endif // INC__Bt_Io_DigitalInputListener__hpp
