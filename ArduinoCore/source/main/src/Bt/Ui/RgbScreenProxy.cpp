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
: mClient(&iClient), mWidth(0), mHeight(0) {

}

//-------------------------------------------------------------------------------------------------

RgbScreenProxy::~RgbScreenProxy() {

}

//-------------------------------------------------------------------------------------------------

size_t RgbScreenProxy::width() {
   if (mWidth == 0) {
      mClient->out() << static_cast<uint8_t>(WIDTH);
      mClient->sendQueryRequest();
      mWidth = mClient->in().readUInt8();
   }

   return mWidth;
}

//-------------------------------------------------------------------------------------------------

size_t RgbScreenProxy::height() {
   if (mHeight == 0) {
      mClient->out() << static_cast<uint8_t>(HEIGHT);
      mClient->sendQueryRequest();
      mHeight = mClient->in().readUInt8();
   }
   return mHeight;
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::setPixel(uint8_t iX, uint8_t iY, Color iColor) {
   mClient->out() << static_cast<uint8_t>(SET_PIXEL) << iX << iY << iColor;
   mClient->sendActionRequest();
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::fill(Color iColor) {
   mClient->out() << static_cast<uint8_t>(FILL) << iColor;
   mClient->sendActionRequest();
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::repaint() {
   mClient->out() << static_cast<uint8_t>(REPAINT);
   mClient->sendActionRequest();
}

//-------------------------------------------------------------------------------------------------

} // namespace Ui
} // namespace Bt
