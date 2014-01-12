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
#include <Bt/Io/DigitalInputListener.hpp>
#include <Bt/Workcycle/MainWorkcycle.hpp>

#include "Settings.hpp"
#include "Image.hpp"
#include "ImageRepository.hpp"

//-------------------------------------------------------------------------------------------------

static const Bt::Ui::Color BLACK     (  0,  0,  0);

//-------------------------------------------------------------------------------------------------

class ImageScroller {

   public:

      ImageScroller(Bt::Ui::I_RgbScreen& iScreen)
      : mCurrentIndex(0), mScreen(&iScreen) {
      }




      void next(bool iValue) {
         if (!iValue) {
            return;
         }

         uint8_t previousIndex = mCurrentIndex;

         mCurrentIndex++ ;
         if (mCurrentIndex >= ImageRepository::size()) {
            mCurrentIndex = 0;
         }
         drawNext(previousIndex);
      }

      void previous(bool iValue) {
         if (!iValue) {
            return;
         }

         uint8_t previousIndex = mCurrentIndex;

         if (mCurrentIndex <= 0) {
            mCurrentIndex = ImageRepository::size();
         }
         mCurrentIndex-- ;
         drawPrevious(previousIndex);
      }

      void draw() {
         ImageRepository::getImage(mCurrentIndex).draw(*mScreen);
         mScreen->repaint();
      }

      void drawNext(uint8_t iPreviousIndex) {
         for(uint8_t x = 0; x < Image::SIZE ; x++) {
            ImageRepository::getImage(iPreviousIndex).draw(*mScreen, 0, x, Image::SIZE-x);
            ImageRepository::getImage(mCurrentIndex).draw(*mScreen, Image::SIZE-x, 0, x);
            mScreen->repaint();
         }
         draw();
      }

      void drawPrevious(uint8_t iPreviousIndex) {
         for(uint8_t x = 0; x < Image::SIZE ; x++) {
            ImageRepository::getImage(iPreviousIndex).draw(*mScreen, x, 0, Image::SIZE-x);
            ImageRepository::getImage(mCurrentIndex).draw(*mScreen, 0, Image::SIZE-x, x);
            mScreen->repaint();
         }
         draw();
      }



   private:
      uint8_t mCurrentIndex;
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


   ImageScroller imageScroller(screen[0]);

   Bt::Io::CapacitiveSensorInput capacitiveInputNext(CAPACITIVE_SENSOR_SEND_PIN,
                                                     CAPACITIVE_SENSOR_NEXT_RECEIVE_PIN,
                                                     CAPACITIVE_SENSOR_HIGH_THRESHOLD,
                                                     CAPACITIVE_SENSOR_LOW_THRESHOLD);
   Bt::Io::CapacitiveSensorInput capacitiveInputPrevious(CAPACITIVE_SENSOR_SEND_PIN,
                                                     CAPACITIVE_SENSOR_PREVIOUS_RECEIVE_PIN,
                                                     CAPACITIVE_SENSOR_HIGH_THRESHOLD,
                                                     CAPACITIVE_SENSOR_LOW_THRESHOLD);

   Bt::Io::DigitalInput buttonNext(capacitiveInputNext);
   Bt::Io::DigitalInput buttonPrevious(capacitiveInputPrevious);

   Bt::Io::DigitalInputListener<ImageScroller> listenerNext(imageScroller, &ImageScroller::next);
   Bt::Io::DigitalInputListener<ImageScroller> listenerPrevious(imageScroller, &ImageScroller::previous);

   buttonNext.add(listenerNext);
   buttonPrevious.add(listenerPrevious);

   workcycle.add(buttonNext);
   workcycle.add(buttonPrevious);

   screen[0].fill(BLACK);
   screen[0].repaint();

   Serial.println("s2");

   imageScroller.draw();

   workcycle.run();

   return 0;
}

//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
