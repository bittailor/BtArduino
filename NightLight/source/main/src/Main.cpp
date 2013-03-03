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
#include <Bt/Util/Vector.hpp>
#include <Bt/Com/TwoWireClient.hpp>
#include <Bt/Com/Twi.hpp>
#include <Bt/Ui/Colorduino.hpp>
#include <Bt/Ui/RgbScreenProxy.hpp>
#include <Bt/Ui/RgbScreenServer.hpp>
#include <Bt/Ui/CompoundRgbScreen.hpp>
#include <Bt/Io/CapacitiveSensorInput.hpp>
#include <Arduino.h>
#include <new.h>
#include <Bt/Io/DigitalInput.hpp>
#include <Bt/Workcycle/MainWorkcycle.hpp>

#include "Settings.hpp"
#include "Image.hpp"
#include "ImageRepository.hpp"

//-------------------------------------------------------------------------------------------------

static const Bt::Ui::Color BLACK     (  0,  0,  0);

//-------------------------------------------------------------------------------------------------

class DrawListener : public Bt::Io::I_DigitalInputListener {

   public:

      DrawListener(uint8_t iIndex, Bt::Ui::I_RgbScreen& iScreen)
      : mIndex(iIndex), mScreen(&iScreen) {
      }

      virtual void high() {
         ImageRepository::getImage(mIndex).draw(*mScreen);
         mScreen->repaint();
      }

      virtual void low() {
      }

   private:
      uint8_t mIndex;
      Bt::Ui::I_RgbScreen* mScreen;

};


//-------------------------------------------------------------------------------------------------

int main() {

   init();

   delay(STARTUP_DELAY);

   Serial.begin(9600);

   Serial.println("s0");

   // I2C slaves
   Bt::Com::Twi twi;
   Bt::Com::TwoWireClient<Bt::Com::Twi> server1(twi,1);
   Bt::Com::TwoWireClient<Bt::Com::Twi> server2(twi,2);
   Bt::Com::TwoWireClient<Bt::Com::Twi> server3(twi,3);
   Bt::Com::TwoWireClient<Bt::Com::Twi> server4(twi,4);


   // I2C led matrix proxies
   Bt::Ui::RgbScreenProxy proxy1(server1);
   Bt::Ui::RgbScreenProxy proxy2(server2);
   Bt::Ui::RgbScreenProxy proxy3(server3);
   Bt::Ui::RgbScreenProxy proxy4(server4);

   // Combine led matrixes to compund screen
   Bt::Util::Vector<Bt::Ui::CompoundRgbScreen,1> screen;
   {
      Bt::Util::StaticMatrix<Bt::Ui::I_RgbScreen*,2,2> screens;
      screens(0,0) = &proxy1;
      screens(0,1) = &proxy2;
      screens(1,0) = &proxy3;
      screens(1,1) = &proxy4;
      screen.pushBack<Bt::Util::I_Matrix<Bt::Ui::I_RgbScreen*>&>(screens);
   }
   Serial.println("s1");

   Bt::Workcycle::MainWorkcycle workcycle;


   Bt::Util::Vector<Bt::Io::CapacitiveSensorInput,NUMBER_OF_BUTTONS> capacitiveInputs;
   Bt::Util::Vector<Bt::Io::DigitalInput,NUMBER_OF_BUTTONS> buttons;
   Bt::Util::Vector<DrawListener,NUMBER_OF_BUTTONS> listeners;

   for(uint8_t i = 0 ; i < NUMBER_OF_BUTTONS ; i++ ) {
      capacitiveInputs.pushBack(CAPACITIVE_SENSOR_SEND_PIN,
                                CAPACITIVE_SENSOR_FIRST_RECEIVE_PIN+i,
                                CAPACITIVE_SENSOR_HIGH_THRESHOLD,
                                CAPACITIVE_SENSOR_LOW_THRESHOLD);
      buttons.pushBack<Bt::Io::I_RawInput<bool>&>(capacitiveInputs[i]);
      listeners.pushBack<uint8_t,Bt::Ui::I_RgbScreen&>(i, screen[0]);
      buttons[i].add(listeners[i]);
      workcycle.add(buttons[i]);
   }

   screen[0].fill(BLACK);
   screen[0].repaint();

   Serial.println("s2");

   workcycle.run();

   return 0;
}

//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
