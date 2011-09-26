//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoScreenMaster
//
//-------------------------------------------------------------------------------------------------
//
//  Main
//  
//*************************************************************************************************

#include <wiring.h>
#include <Wire.h>
#include <Bt/Ui/Colorduino.hpp>
#include <Bt/Ui/RgbScreenProxy.hpp>


int main() {
   init();

   Wire.begin();

   Bt::Ui::RgbScreenProxy proxy1(1);
   Bt::Ui::RgbScreenProxy proxy2(2);

   Bt::Ui::Color colors[] = {
      Bt::Ui::Color(255,255,255),
      Bt::Ui::Color(  0,  0,255),
      Bt::Ui::Color(  0,255,  0),
      Bt::Ui::Color(255,  0,  0),
      Bt::Ui::Color(  0,  0,  0)
   };

   int d = 200;

   while(true) {
      for (unsigned int i = 0; i < sizeof(colors)/sizeof(colors[0]) ; ++i) {
         proxy1.fill(colors[i]);
         proxy2.fill(colors[i]);
         proxy1.repaint();
         proxy2.repaint();
         delay(d);
      }
   }

   return 0;
}
