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

#include "Bt/Ui/RemoteRgbScreenProtocol.hpp"

namespace Bt {
namespace Ui {


//-------------------------------------------------------------------------------------------------

RgbScreenProxy::RgbScreenProxy(Bt::Com::I_RequestClient& iClient)
: mClient(&iClient), mWidth(0), mHeight(0), mSegments(0) {

}

//-------------------------------------------------------------------------------------------------

RgbScreenProxy::~RgbScreenProxy() {

}

//-------------------------------------------------------------------------------------------------

size_t RgbScreenProxy::width() {
   if (mWidth == 0) {
      mClient->out() << RemoteRgbScreenProtocol::WIDTH;
      mClient->sendQueryRequest();
      mWidth = mClient->in().readUInt8();
   }

   return mWidth;
}

//-------------------------------------------------------------------------------------------------

size_t RgbScreenProxy::height() {
   if (mHeight == 0) {
      mClient->out() << RemoteRgbScreenProtocol::HEIGHT;
      mClient->sendQueryRequest();
      mHeight = mClient->in().readUInt8();
   }
   return mHeight;
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::setPixel(uint8_t iX, uint8_t iY, Color iColor) {
   mClient->out() << RemoteRgbScreenProtocol::SET_PIXEL << iX << iY << iColor;
   mClient->sendActionRequest();
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::fill(Color iColor) {
   mClient->out() << RemoteRgbScreenProtocol::FILL << iColor;
   mClient->sendActionRequest();
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::repaint() {
   mClient->out() << RemoteRgbScreenProtocol::REPAINT;
   mClient->sendActionRequest();
}


//-------------------------------------------------------------------------------------------------

uint8_t RgbScreenProxy::numberOfSegments() {
   if (mSegments == 0) {
      mClient->out() << RemoteRgbScreenProtocol::NUMBER_OF_SEGMENTS;
      mClient->sendQueryRequest();
      mSegments = mClient->in().readUInt8();
   }
   return mSegments;
}

//-------------------------------------------------------------------------------------------------

Color RgbScreenProxy::whiteBalance(uint8_t iSegment) {
   mClient->out() << RemoteRgbScreenProtocol::WHITE_BALANCE << iSegment;
   mClient->sendQueryRequest();
   return Color(mClient->in());
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::setWhiteBalance(Color iColor, uint8_t iSegment) {
   mClient->out() << RemoteRgbScreenProtocol::SET_WHITE_BALANCE << iColor << iSegment;
   mClient->sendActionRequest();
}

//-------------------------------------------------------------------------------------------------

void RgbScreenProxy::persistWhiteBalance(uint8_t iSegment) {
   mClient->out() << RemoteRgbScreenProtocol::PERSIST_WHITE_BALANCE << iSegment;
   mClient->sendActionRequest();
}

//-------------------------------------------------------------------------------------------------

} // namespace Ui
} // namespace Bt
