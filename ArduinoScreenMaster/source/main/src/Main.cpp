//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoScreenMaster
//
//-------------------------------------------------------------------------------------------------
//
//  Main
//  
//*************************************************************************************************

#include <Arduino.h>
#include <Bt/Ui/Colorduino.hpp>
#include <Bt/Ui/RgbScreenProxy.hpp>
#include <Bt/Ui/CompoundRgbScreen.hpp>
#include <Bt/Com/TwoWireClient.hpp>
#include <Bt/Com/Twi.hpp>

static const unsigned long STARTUP_DELAY = 3000 ; // 3s


int main() {


   init();

   //Serial.begin(9600);

   delay(STARTUP_DELAY);

   Bt::Com::Twi twi;

   Bt::Com::TwoWireClient<Bt::Com::Twi> server1(twi,1);
   Bt::Com::TwoWireClient<Bt::Com::Twi> server2(twi,2);

   Bt::Ui::RgbScreenProxy proxy1(server1);
   Bt::Ui::RgbScreenProxy proxy2(server2);
   Bt::Util::StaticMatrix<Bt::Ui::I_RgbScreen*,1,2> screens;
   screens(0,0) = &proxy1;
   screens(0,1) = &proxy2;

   Bt::Ui::CompoundRgbScreen screen(screens);



   Bt::Ui::Color black     (  0,  0,  0);
   Bt::Ui::Color red       (255,  0,  0);
   Bt::Ui::Color green     (  0,255,  0);
   Bt::Ui::Color blue      (  0,  0,255);
   Bt::Ui::Color yellow    (255,255,  0);
   Bt::Ui::Color white     (255,255,255);

   /*Bt::Ui::Color colors[] = {
      Bt::Ui::Color(255,255,255),
      Bt::Ui::Color(  0,  0,255),
      Bt::Ui::Color(  0,255,  0),
      Bt::Ui::Color(255,  0,  0),
      Bt::Ui::Color(  0,  0,  0)
   };
   */


   int d = 10;

   proxy1.fill(green);
   proxy1.repaint();
   proxy2.fill(red);
   proxy2.repaint();
   delay(d);
   proxy1.fill(black);
   proxy1.repaint();
   proxy2.fill(black);
   proxy2.repaint();
   delay(d);

   while(true) {
      for (size_t y = 0; y < screen.height(); ++y) {
         for (size_t x = 0; x < screen.width(); ++x) {
            screen.setPixel(x,y,green);
            screen.repaint();
            delay(d);
         }
      }
      for (size_t y = 0; y < screen.height(); ++y) {
         for (size_t x = 0; x < screen.width(); ++x) {
            screen.setPixel(x,y,blue);
         }
      }
      screen.repaint();

      delay(1000);

      screen.fill(black);
      screen.repaint();
      delay(d);
      for (size_t i = 0 ; i < screen.width() ; ++i) {
         screen.setPixel(i,0,green);
         screen.repaint();
         delay(d);
      }
      for (size_t i = 0 ; i < screen.height() ; ++i) {
         screen.setPixel(i,i,red);
         screen.repaint();
         delay(d);
      }
      for (size_t i = 0 ; i < screen.height() ; ++i) {
         screen.setPixel(screen.width()/2+i,screen.height()-1-i,red);
         screen.repaint();
         delay(d);
      }

      for (size_t i = 0; i < screen.height() ; ++i) {
         screen.setPixel(0,screen.height()-1-i,blue);
         screen.repaint();
         delay(d);
      }

      for (size_t i = 0; i < screen.height() ; ++i) {
         screen.setPixel(screen.width()-1,screen.height()-1-i,blue);
         screen.repaint();
         delay(d);
      }


      for (int l = screen.height()-1; l > 2; --l) {
         for (size_t i = 0 ; i < screen.width() ; ++i) {
            screen.setPixel(screen.width()-1-i,l,yellow);
         }
      }

      screen.repaint();
      delay(d);

      delay(1000);
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
