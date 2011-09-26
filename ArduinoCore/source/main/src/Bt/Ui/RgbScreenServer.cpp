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

#include <Wire.h>

#include "Bt/Ui/RgbScreenProxy.hpp"

namespace Bt {
namespace Ui {


void onReceiveCallback(int iNumberOfBytes) {
   Bt::Util::Singleton<Bt::Ui::RgbScreenServer>::instance()->receive(iNumberOfBytes);
}

//-------------------------------------------------------------------------------------------------

RgbScreenServer::RgbScreenServer(I_RgbScreen& iScreen)
:mScreen(iScreen), mSingletonInstance(*this) {
   Wire.onReceive(&onReceiveCallback);
}

//-------------------------------------------------------------------------------------------------

RgbScreenServer::~RgbScreenServer() {
   Wire.onReceive(0);
}

//-------------------------------------------------------------------------------------------------

void RgbScreenServer::receive(int iNumberOfBytes) {

   uint8_t* data = new uint8_t[iNumberOfBytes];
   int i = 0;
   while(Wire.available() && i < iNumberOfBytes) {
      if (Wire.available()) {
         data[i] = Wire.receive();
         i++;
      }
   }

   switch(data[0]) {
      case RgbScreenProxy::SET_PIXEL : {
         setPixel(data);
      } break;
      case RgbScreenProxy::FILL : {
         fill(data);
      } break;
      case RgbScreenProxy::REPAINT : {
         repaint(data);
      } break;
      default : {
      } break;
   }

   delete data;
}

//-------------------------------------------------------------------------------------------------

void RgbScreenServer::setPixel(uint8_t iData[]) {
   mScreen.setPixel(iData[1],iData[2],Color(iData[3],iData[4],iData[5]));
}

//-------------------------------------------------------------------------------------------------

void RgbScreenServer::fill(uint8_t iData[]) {
   mScreen.fill(Color(iData[1],iData[2],iData[3]));
}

//-------------------------------------------------------------------------------------------------

void RgbScreenServer::repaint(uint8_t iData[]) {
   mScreen.repaint();
}

//-------------------------------------------------------------------------------------------------

} // namespace Ui
} // namespace Bt
