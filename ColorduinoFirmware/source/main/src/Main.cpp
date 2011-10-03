//*************************************************************************************************
//
//  BITTAILOR.CH - ColorduinoFirmware
//
//-------------------------------------------------------------------------------------------------
//
//  Main
//  
//*************************************************************************************************

#include <WProgram.h>
#include <wiring.h>
#include <Wire.h>
#include <Bt/Ui/Colorduino.hpp>
#include <Bt/Ui/RgbScreenServer.hpp>


int main() {
   init();

   //Serial.begin(9600);

   uint8_t address = 1;

   Wire.begin(address);

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

   while(true) {
      delay(100);
   }

   return 0;
}
