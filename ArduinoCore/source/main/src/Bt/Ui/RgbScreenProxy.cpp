//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::RgbScreenProxy
//  
//*************************************************************************************************

#include "Bt/Ui/RgbScreenProxy.hpp"

#include <wiring.h>
#include <Wire.h>

namespace Bt {
namespace Ui {


//-------------------------------------------------------------------------------------------------

RgbScreenProxy::RgbScreenProxy(uint8_t iRemoteAddress)
: mRemoteAddress(iRemoteAddress){

}

//-------------------------------------------------------------------------------------------------

RgbScreenProxy::~RgbScreenProxy() {

}

//-------------------------------------------------------------------------------------------------

size_t RgbScreenProxy::width() {
   // TODO Bt: Get width from server
   return 8;
}

//-------------------------------------------------------------------------------------------------

size_t RgbScreenProxy::height() {
   // TODO Bt: Get height from server
   return 8;
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::setPixel(uint8_t iX, uint8_t iY, Color iColor) {
   Wire.beginTransmission(mRemoteAddress);
   uint8_t data[] = {SET_PIXEL,iX,iY,iColor.red(),iColor.green(),iColor.blue()};
   Wire.send(data,sizeof(data)/sizeof(data[0]));
   send();
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::fill(Color iColor) {
   Wire.beginTransmission(mRemoteAddress);
   uint8_t data[] = {FILL,iColor.red(),iColor.green(),iColor.blue()};
   Wire.send(data,sizeof(data)/sizeof(data[0]));
   send();
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::repaint() {
   Wire.beginTransmission(mRemoteAddress);
   uint8_t data[] = {REPAINT};
   Wire.send(data,sizeof(data)/sizeof(data[0]));
   send();
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::send() {
   uint8_t status = Wire.endTransmission();
   if (status != 0) {
      uint8_t retry = 0;
      while (status != 0 && retry < 20) {
         delayMicroseconds(retry);
         status = Wire.endTransmission();
         retry++;
      }
   }
}

//-------------------------------------------------------------------------------------------------

} // namespace Ui
} // namespace Bt
