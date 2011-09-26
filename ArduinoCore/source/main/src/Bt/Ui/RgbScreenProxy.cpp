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

void RgbScreenProxy::setPixel(uint8_t iX, uint8_t iY, Color iColor) {
   Wire.beginTransmission(mRemoteAddress);
   uint8_t data[] = {SET_PIXEL,iX,iY,iColor.red(),iColor.green(),iColor.blue()};
   Wire.send(data,sizeof(data)/sizeof(data[0]));
   Wire.endTransmission();
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::fill(Color iColor) {
   Wire.beginTransmission(mRemoteAddress);
   uint8_t data[] = {FILL,iColor.red(),iColor.green(),iColor.blue()};
   Wire.send(data,sizeof(data)/sizeof(data[0]));
   Wire.endTransmission();
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::repaint() {
   Wire.beginTransmission(mRemoteAddress);
   uint8_t data[] = {REPAINT};
   Wire.send(data,sizeof(data)/sizeof(data[0]));
   Wire.endTransmission();
}

//-------------------------------------------------------------------------------------------------

} // namespace Ui
} // namespace Bt
