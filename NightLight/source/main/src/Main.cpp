//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoScreenMaster
//
//-------------------------------------------------------------------------------------------------
//
//  Main
//  
//*************************************************************************************************

#include <Bt/Util/Delay.hpp>
#include <Bt/Com/TwoWireClient.hpp>
#include <Bt/Com/Twi.hpp>
#include <Bt/Ui/Colorduino.hpp>
#include <Bt/Ui/RgbScreenProxy.hpp>
#include <Bt/Ui/RgbScreenServer.hpp>
#include <Bt/Ui/CompoundRgbScreen.hpp>
#include <Bt/Io/CapacitiveSensorInput.hpp>
#include <Arduino.h>
#include <Bt/Io/DigitalInput.hpp>
#include <Bt/Workcycle/MainWorkcycle.hpp>

#include "Star.hpp"



//-------------------------------------------------------------------------------------------------

// 3s for the I2C slaves to start
#define STARTUP_DELAY 3000UL

static const Bt::Ui::Color RED       (255,  0,  0);
static const Bt::Ui::Color YELLOW    (255,255,  0);
static const Bt::Ui::Color GREEN     (  0,255,  0);
static const Bt::Ui::Color BLACK     (  0,  0,  0);

//-------------------------------------------------------------------------------------------------

class DrawListener : public Bt::Io::I_DigitalInputListener {

   public:
      typedef void (*DrawFunction)(Bt::Ui::I_RgbScreen&);

      DrawListener(DrawFunction iDrawFunction, Bt::Ui::I_RgbScreen& iScreen)
      : mDrawFunction(iDrawFunction), mScreen(&iScreen) {
      }

      virtual void high() {
         mDrawFunction(*mScreen);
      }

      virtual void low() {
      }

   private:
      DrawFunction mDrawFunction;
      Bt::Ui::I_RgbScreen* mScreen;

};


//-------------------------------------------------------------------------------------------------

int main() {

   init();

   delay(STARTUP_DELAY);

   Serial.begin(9600);

   Serial.println("start");

   // I2C slaves
   Bt::Com::Twi twi;
   Bt::Com::TwoWireClient<Bt::Com::Twi> server1(twi,1);
   Bt::Com::TwoWireClient<Bt::Com::Twi> server2(twi,2);
   Bt::Com::TwoWireClient<Bt::Com::Twi> server3(twi,3);
   Bt::Com::TwoWireClient<Bt::Com::Twi> server4(twi,4);

     Serial.println("slaves ok");

   // I2C led matrix proxies
   Bt::Ui::RgbScreenProxy proxy1(server1);
   Bt::Ui::RgbScreenProxy proxy2(server2);
   Bt::Ui::RgbScreenProxy proxy3(server3);
   Bt::Ui::RgbScreenProxy proxy4(server4);

   Serial.println("proxies ok");

   // Combine led matrixes to compund screen
   Bt::Util::StaticMatrix<Bt::Ui::I_RgbScreen*,2,2> screens;
   screens(0,0) = &proxy1;
   screens(0,1) = &proxy2;
   screens(1,0) = &proxy3;
   screens(1,1) = &proxy4;
   Bt::Ui::CompoundRgbScreen screen(screens);

   Serial.println("screen ok");



   Bt::Io::CapacitiveSensorInput capacitiveInputButton1(3,4,150,100);
   Bt::Io::CapacitiveSensorInput capacitiveInputButton2(3,5,150,100);
   Bt::Io::CapacitiveSensorInput capacitiveInputButton3(3,6,150,100);
   Bt::Io::CapacitiveSensorInput capacitiveInputButton4(3,7,150,100);

   Bt::Io::DigitalInput button1(capacitiveInputButton1);
   Bt::Io::DigitalInput button2(capacitiveInputButton2);
   Bt::Io::DigitalInput button3(capacitiveInputButton3);
   Bt::Io::DigitalInput button4(capacitiveInputButton4);

   DrawListener listener1(&drawStar,screen);
   DrawListener listener2(&drawTruck,screen);
   DrawListener listener3(&drawAngel,screen);
   DrawListener listener4(&drawCar3,screen);

   button1.add(listener1);
   button2.add(listener2);
   button3.add(listener3);
   button4.add(listener4);


   Bt::Workcycle::MainWorkcycle workcycle;

   workcycle.add(button1);
   workcycle.add(button2);
   workcycle.add(button3);
   workcycle.add(button4);

   screen.fill(BLACK);
   screen.repaint();

   workcycle.run();

   return 0;
}

//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
