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


   Bt::Ui::Color black(  0,  0,  0);
   Bt::Ui::Color red  (255,  0,  0);
   Bt::Ui::Color green(  0,255,  0);
   Bt::Ui::Color blue (  0,  0,255);
   Bt::Ui::Color white(255,255,255);

   Bt::Ui::Color colors[] = {
      Bt::Ui::Color(255,255,255),
      Bt::Ui::Color(  0,  0,255),
      Bt::Ui::Color(  0,255,  0),
      Bt::Ui::Color(255,  0,  0),
      Bt::Ui::Color(  0,  0,  0)
   };


   int d = 100;

   proxy1.fill(black);
   proxy2.fill(black);

   while(true) {
      proxy1.fill(black);
      proxy1.repaint();
      delay(d);
      for (int i = 0; i < 8; ++i) {
         proxy1.setPixel(i,0,green);
         proxy1.repaint();
         delay(d);
      }
      for (int i = 0; i < 8; ++i) {
         proxy1.setPixel(i,i,red);
         proxy1.repaint();
         delay(d);
      }
      for (int i = 0; i < 8; ++i) {
         proxy1.setPixel(0,7-i,Bt::Ui::Color(100,i*30,255-i*30));
         proxy1.repaint();
         delay(d);
      }
   }


   /*
   while(true) {
      for (unsigned int i = 0; i < sizeof(colors)/sizeof(colors[0]) ; ++i) {
         proxy1.fill(colors[i]);
         proxy2.fill(colors[i]);
         proxy1.repaint();
         proxy2.repaint();
         delay(d);
      }
   }
   */

   return 0;
}
