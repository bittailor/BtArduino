//*************************************************************************************************
//
//  BITTAILOR.CH - ColorduinoFirmware
//
//-------------------------------------------------------------------------------------------------
//
//  Main
//  
//*************************************************************************************************

#include <Arduino.h>
#include <Wire.h>
#include <Bt/Ui/Colorduino.hpp>
#include <Bt/Ui/RgbScreenServer.hpp>
#include <Bt/Com/Twi.hpp>
#include <Bt/Com/TwoWireServer.hpp>


void drawAddress(uint8_t iAddress, Bt::Ui::I_RgbScreen& iScreen, const Bt::Ui::Color& iColor) {
   for (size_t y = 0 ; y < iScreen.height() ; y++) {
      for (size_t x = 0 ; x < iScreen.width() ; x++) {
         if ((x + y) >= iAddress) {

            return;
         }
         iScreen.setPixel(x,y,iColor);
      }
   }
}

int main() {
   init();

   //Serial.begin(9600);

   uint8_t address = 1;

   Bt::Ui::Color red   (255,  0,  0);
   Bt::Ui::Color orange(238,154,  0);
   Bt::Ui::Color green (  0,255,  0);
   Bt::Ui::Color black (  0,  0,  0);

   Bt::Ui::Colorduino colorduino;
   colorduino.fill(red);
   colorduino.repaint();
   Bt::Ui::RgbScreenServer server(colorduino);
   colorduino.fill(orange);
   colorduino.repaint();

   Bt::Com::Twi twi;
   Bt::Com::TwoWireServer<Bt::Com::Twi> twiServer(twi,address,server);

   // show the address of this colorduino
   colorduino.fill(black);
   drawAddress(address,colorduino,green);
   colorduino.repaint();

   // colorduino and communication is interrupt driven
   while(true) {
      delay(100);
   }

   return 0;
}
