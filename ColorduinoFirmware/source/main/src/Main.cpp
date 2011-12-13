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


int main() {
   init();

   //Serial.begin(9600);

   uint8_t address = 1;

   Bt::Ui::Colorduino colorduino;

   Bt::Ui::Color blue(0,0,255);
   Bt::Ui::Color black(0,0,0);

   for (uint8_t i = 0; i < address; ++i) {
      colorduino.fill(blue);
      colorduino.repaint();
      delay(100);
      colorduino.fill(black);
      colorduino.repaint();
      delay(100);
   }

   Bt::Ui::RgbScreenServer server(colorduino);
   Bt::Com::Twi twi;
   Bt::Com::TwoWireServer<Bt::Com::Twi> twiServer(twi,address,server);

   while(true) {
      delay(100);
   }

   return 0;
}
