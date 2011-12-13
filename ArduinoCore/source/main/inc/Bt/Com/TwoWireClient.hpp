//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::TwoWireClient
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_TwoWireClient__hpp
#define INC__Bt_Com_TwoWireClient__hpp

extern "C" {
   #include "twi.h"
}

#include "Bt/Com/I_RequestClient.hpp"
#include "Bt/Com/StaticArrayPackageBuffer.hpp"
#include "Bt/Com/BinaryInputPackage.hpp"
#include "Bt/Com/BinaryOutputPackage.hpp"
#include "Bt/Util/Delay.hpp"

namespace Bt {
namespace Com {

template<typename Twi>
class TwoWireClient : public I_RequestClient
{
   public:
      TwoWireClient(Twi& twi, uint8_t serverAddress);
      ~TwoWireClient();

      virtual Com::I_OutputPackage& out();
      virtual Com::I_InputPackage& in();

      virtual void sendRequest();

   private:
   	  // Constructor to prohibit copy construction.
      TwoWireClient(const TwoWireClient&);

      // Operator= to prohibit copy assignment
      TwoWireClient& operator=(const TwoWireClient&);

      uint8_t send();

      Twi* mTwi;
      uint8_t mAddress;
      StaticArrayPackageBuffer<TWI_BUFFER_LENGTH> mInputBuffer;
      BinaryInputPackage mInput;
      StaticArrayPackageBuffer<TWI_BUFFER_LENGTH> mOutputBuffer;
      BinaryOutputPackage mOutput;
      static bool sInitDone;

};

//-------------------------------------------------------------------------------------------------

template<typename Twi>
bool TwoWireClient<Twi>::sInitDone = false;

//-------------------------------------------------------------------------------------------------

template<typename Twi>
TwoWireClient<Twi>::TwoWireClient(Twi& twi, uint8_t address)
:mTwi(&twi), mAddress(address), mInput(mInputBuffer), mOutput(mOutputBuffer) {
   if(!sInitDone) {
      sInitDone = true;
      mTwi->init();
   }
}

//-------------------------------------------------------------------------------------------------

template<typename Twi>
TwoWireClient<Twi>::~TwoWireClient() {

}

//-------------------------------------------------------------------------------------------------

template<typename Twi>
Com::I_OutputPackage& TwoWireClient<Twi>::out() {
   return mOutput;
}

//-------------------------------------------------------------------------------------------------

template<typename Twi>
Com::I_InputPackage& TwoWireClient<Twi>::in() {
   return mInput;
}

//-------------------------------------------------------------------------------------------------

template<typename Twi>
void TwoWireClient<Twi>::sendRequest() {
   uint8_t status = this->send();
   if (status != 0) {
      uint8_t retry = 0;
      while (status != 0) {
         Util::delayInMilliseconds(retry);
         status = this->send();
         retry++;
         if (retry > 20) {
            // TODO error handling
            return;
         }
      }
   }
   mOutputBuffer.clear();
   mInputBuffer.clear();

   uint8_t answerLentgh = 0;

   mTwi->readFrom(mAddress,&answerLentgh,1);

   if(answerLentgh > 0) {
      uint8_t read = mTwi->readFrom(mAddress,mInputBuffer.raw(),answerLentgh);
      mInputBuffer.filled(read);
   }
}

//-------------------------------------------------------------------------------------------------

template<typename Twi>
uint8_t TwoWireClient<Twi>::send() {
   return mTwi->writeTo(mAddress,mOutputBuffer.raw(),mOutputBuffer.length(),1);
}

//-------------------------------------------------------------------------------------------------

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_TwoWireClient__hpp
