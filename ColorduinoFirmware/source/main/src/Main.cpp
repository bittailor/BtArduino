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

   Serial.begin(9600);

   //Wire.begin(1);
   Wire.begin(2);

   Bt::Ui::Colorduino colorduino;
   Bt::Ui::RgbScreenServer server(colorduino);

   while(true) {
      delay(100);
   }

   return 0;
}
