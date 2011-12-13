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

namespace Bt {
namespace Ui {


//-------------------------------------------------------------------------------------------------

RgbScreenProxy::RgbScreenProxy(Bt::Com::I_RequestClient& iClient)
: client(&iClient) {

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
   client->out() << static_cast<uint8_t>(SET_PIXEL) << iX << iY << iColor;
   client->sendRequest();
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::fill(Color iColor) {
   client->out() << static_cast<uint8_t>(FILL) << iColor;
   client->sendRequest();
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::repaint() {
   client->out() << static_cast<uint8_t>(REPAINT);
   client->sendRequest();
}

//-------------------------------------------------------------------------------------------------

} // namespace Ui
} // namespace Bt
