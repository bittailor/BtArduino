//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::TwoWireServer
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_TwoWireServer__hpp
#define INC__Bt_Com_TwoWireServer__hpp

#include <stdint.h>

extern "C" {
   #include "twi.h"
}

#include "Bt/Com/StaticArrayPackageBuffer.hpp"
#include "Bt/Com/BinaryInputPackage.hpp"
#include "Bt/Com/BinaryOutputPackage.hpp"
#include <Bt/Com/I_RequestServer.hpp>

namespace Bt {
namespace Com {

template<typename Twi>
class TwoWireServer 
{
   public:
      TwoWireServer(Twi& twi, uint8_t address, I_RequestServer& iHandler);
      ~TwoWireServer();
   
   private:
   	  // Constructor to prohibit copy construction.
      TwoWireServer(const TwoWireServer&);

      // Operator= to prohibit copy assignment
      TwoWireServer& operator=(const TwoWireServer&);

      void request();
      void receive(uint8_t* iData, int iNumberOfBytes);

      Twi* mTwi;
      StaticArrayPackageBuffer<TWI_BUFFER_LENGTH> mInputBuffer;
      BinaryInputPackage mInput;
      StaticArrayPackageBuffer<TWI_BUFFER_LENGTH> mOutputBuffer;
      BinaryOutputPackage mOutput;
      bool mAnswerLengthSent;
      I_RequestServer* mHandler;


      static TwoWireServer* sInstance;
      static void onRequestService();
      static void onReceiveService(uint8_t* iData, int iNumberOfBytes);
};

//-------------------------------------------------------------------------------------------------

template<typename Twi>
TwoWireServer<Twi>* TwoWireServer<Twi>::sInstance = 0;

//-------------------------------------------------------------------------------------------------

template<typename Twi>
void TwoWireServer<Twi>::onRequestService(void) {
   if (sInstance != 0) {
      sInstance->request();
   }
}

//-------------------------------------------------------------------------------------------------

template<typename Twi>
void TwoWireServer<Twi>::onReceiveService(uint8_t* iData, int iNumberOfBytes) {
   if (sInstance != 0) {
      sInstance->receive(iData,iNumberOfBytes);
   }
}

//-------------------------------------------------------------------------------------------------

template<typename Twi>
TwoWireServer<Twi>::TwoWireServer(Twi& twi, uint8_t address, I_RequestServer& iHandler)
:mTwi(&twi), mInput(mInputBuffer), mOutput(mOutputBuffer), mAnswerLengthSent(false), mHandler(&iHandler) {
   if (sInstance == 0) {
      sInstance = this;
      mTwi->setAddress(address);
      mTwi->attachSlaveTxEvent(&TwoWireServer<Twi>::onRequestService);
      mTwi->attachSlaveRxEvent(&TwoWireServer<Twi>::onReceiveService);
      mTwi->init();
   }
   // TODO what should we do in the error case ?
}

//-------------------------------------------------------------------------------------------------

template<typename Twi>
TwoWireServer<Twi>::~TwoWireServer() {

}

//-------------------------------------------------------------------------------------------------

template<typename Twi>
void TwoWireServer<Twi>::request(void) {
   if (mAnswerLengthSent) {
      if(mTwi->transmit(mOutputBuffer.raw(), mOutputBuffer.length()) == 0) {
         mOutputBuffer.clear();
      }
   } else {
      uint8_t length = mOutputBuffer.length();
      if (mTwi->transmit(&length, 1) == 0) {
         mAnswerLengthSent = true;
      }
   }
}

//-------------------------------------------------------------------------------------------------

template<typename Twi>
void TwoWireServer<Twi>::receive(uint8_t* iData, int iNumberOfBytes ) {
   mOutputBuffer.clear();
   mInputBuffer.clear();
   mAnswerLengthSent = false;
   for (int i = 0; i < iNumberOfBytes; ++i) {
      mInputBuffer.put(iData[i]);
   }

   mHandler->handleRequest(mInput,mOutput);
}

//-------------------------------------------------------------------------------------------------

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_TwoWireServer__hpp
