//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::TwiGMock
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_TwiGMock__hpp
#define INC__Bt_Com_TwiGMock__hpp

#include <gmock/gmock.h>

namespace Bt {
namespace Com {

class TwiGMock {
   public:
      MOCK_METHOD0(init,void ());
      MOCK_METHOD1(setAddress,void (uint8_t address));
      MOCK_METHOD3(readFrom,uint8_t (uint8_t address, uint8_t* data, uint8_t length));
      MOCK_METHOD4(writeTo,uint8_t (uint8_t address, uint8_t* data, uint8_t length, uint8_t wait));
      MOCK_METHOD2(transmit,uint8_t (const uint8_t* data, uint8_t length));
      MOCK_METHOD1(attachSlaveRxEvent,void ( void (*function)(uint8_t*, int) ));
      MOCK_METHOD1(attachSlaveTxEvent,void ( void (*function)(void) ));
      
};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_TwiGMock__hpp
