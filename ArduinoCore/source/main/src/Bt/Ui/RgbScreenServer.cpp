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

#include "Bt/Ui/RemoteRgbScreenProtocol.hpp"
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
      case RemoteRgbScreenProtocol::WIDTH : {
         oOut << static_cast<uint8_t>(mScreen->width());
      } break;
      case RemoteRgbScreenProtocol::HEIGHT : {
         oOut << static_cast<uint8_t>(mScreen->height());
      } break;
      case RemoteRgbScreenProtocol::SET_PIXEL : {
         setPixel(iIn,oOut);
      } break;
      case RemoteRgbScreenProtocol::FILL : {
         fill(iIn,oOut);
      } break;
      case RemoteRgbScreenProtocol::REPAINT : {
         repaint(iIn,oOut);
      } break;
      case RemoteRgbScreenProtocol::NUMBER_OF_SEGMENTS : {
         oOut << static_cast<uint8_t>(mScreen->numberOfSegments());
      } break;
      case RemoteRgbScreenProtocol::WHITE_BALANCE : {
         oOut << mScreen->whiteBalance(iIn.readUInt8());
      } break;
      case RemoteRgbScreenProtocol::SET_WHITE_BALANCE : {
         setWhiteBalance(iIn,oOut);
      } break;
      case RemoteRgbScreenProtocol::PERSIST_WHITE_BALANCE : {
         mScreen->persistWhiteBalance(iIn.readUInt8());
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

void RgbScreenServer::setWhiteBalance(Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut) {
   Color color(iIn);
   uint8_t segment;
   iIn >> segment;
   mScreen->setWhiteBalance(color,segment);
}

//-------------------------------------------------------------------------------------------------

} // namespace Ui
} // namespace Bt
