//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::Twi
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_Twi__hpp
#define INC__Bt_Com_Twi__hpp

extern "C" {
   #include "twi.h"
}

namespace Bt {
namespace Com {

class Twi 
{
   public:

      void init() {
         twi_init();
      }
      void setAddress(uint8_t address) {
         twi_setAddress(address);
      }
      uint8_t readFrom(uint8_t address, uint8_t* data, uint8_t length) {
         return twi_readFrom(address,data,length);
      }
      uint8_t writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait) {
         return twi_writeTo(address,data,length,wait);
      }
      uint8_t transmit(const uint8_t* data, uint8_t length) {
         return twi_transmit(data,length);
      }
      void attachSlaveRxEvent( void (*function)(uint8_t*, int) ) {
         return twi_attachSlaveRxEvent(function);
      }
      void attachSlaveTxEvent( void (*function)(void) ) {
         return twi_attachSlaveTxEvent(function);
      }

};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_Twi__hpp
