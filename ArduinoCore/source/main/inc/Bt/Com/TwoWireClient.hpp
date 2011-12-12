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

#include "Bt/Com/I_RequestClient.hpp"
#include "Bt/Util/Delay.hpp"

namespace Bt {
namespace Com {

template<typename Twi>
class TwoWireClient : public I_RequestClient
{
   public:
      TwoWireClient(Twi& twi, uint8_t serverAddress);
      ~TwoWireClient();

      virtual void sendRequest(Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut);

   private:
   	  // Constructor to prohibit copy construction.
      TwoWireClient(const TwoWireClient&);

      // Operator= to prohibit copy assignment
      TwoWireClient& operator=(const TwoWireClient&);

      uint8_t send(uint8_t* iData, uint8_t iLength);

      Twi* mTwi;
      uint8_t mAddress;

      static bool sInitDone;

};

//-------------------------------------------------------------------------------------------------

template<typename Twi>
bool TwoWireClient<Twi>::sInitDone = false;

//-------------------------------------------------------------------------------------------------

template<typename Twi>
TwoWireClient<Twi>::TwoWireClient(Twi& twi, uint8_t address)
:mTwi(&twi), mAddress(address) {
   if(!sInitDone) {
      sInitDone = true;
      twi_init();
   }
}

//-------------------------------------------------------------------------------------------------

template<typename Twi>
void TwoWireClient<Twi>::sendRequest(Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut) {
   uint8_t status = this->send(iIn.buffer().raw(),iIn.buffer().length());
   if (status != 0) {
      uint8_t retry = 0;
      while (status != 0) {
         Util::delayInMilliseconds(retry);
         status = send();
         retry++;
         if (retry > 20) {
            // TODO error handling
            return;
         }
      }
   }
   iIn.buffer().clear();

   uint8_t answerLentgh = 0;

   mTwi->readFrom(mAddress,&answerLentgh,1);

   if(answerLentgh > 0) {
      uint8_t read = mTwi->readFrom(mAddress,iIn.buffer().raw(),answerLentgh);
      oOut.buffer().filled(read);
   }
}

//-------------------------------------------------------------------------------------------------

template<typename Twi>
uint8_t TwoWireClient<Twi>::send(uint8_t* iData, uint8_t iLength) {
   return mTwi->writeTo(mAddress, iData, iLength, 1);
}

//-------------------------------------------------------------------------------------------------

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_TwoWireClient__hpp
