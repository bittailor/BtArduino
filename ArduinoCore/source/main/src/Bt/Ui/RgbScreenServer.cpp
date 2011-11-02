//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::RgbScreenServer
//  
//*************************************************************************************************

#include "Bt/Ui/RgbScreenServer.hpp"

#include "Bt/Ui/RgbScreenProxy.hpp"

namespace Bt {
namespace Ui {


//-------------------------------------------------------------------------------------------------

RgbScreenServer::RgbScreenServer(I_RgbScreen& iScreen)
:mScreen(&iScreen) {
}

//-------------------------------------------------------------------------------------------------

RgbScreenServer::~RgbScreenServer() {
}

//-------------------------------------------------------------------------------------------------

void RgbScreenServer::handleRequest(Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut) {
   uint8_t command = 255;
   iIn >> command;
   switch (command) {
      case RgbScreenProxy::SET_PIXEL : {
         setPixel(iIn,oOut);
      } break;
      case RgbScreenProxy::FILL : {
         fill(iIn,oOut);
      } break;
      case RgbScreenProxy::REPAINT : {
         repaint(iIn,oOut);
      } break;
      default : {
      } break;
   }
}

//-------------------------------------------------------------------------------------------------

void RgbScreenServer::setPixel(Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut) {
   uint8_t x = 0;
   uint8_t y = 0;
   iIn >> x >> y;
   Color color(iIn);
   mScreen->setPixel(x,y,color);
}

//-------------------------------------------------------------------------------------------------

void RgbScreenServer::fill(Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut) {
   Color color(iIn);
   mScreen->fill(color);
}

//-------------------------------------------------------------------------------------------------

void RgbScreenServer::repaint(Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut) {
   mScreen->repaint();
}

//-------------------------------------------------------------------------------------------------

} // namespace Ui
} // namespace Bt
