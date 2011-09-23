//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::Colorduino
//  
//*************************************************************************************************

#ifndef INC__Bt_Ui_Colorduino__hpp
#define INC__Bt_Ui_Colorduino__hpp

#include <Bt/Util/Singleton.hpp>
#include <Bt/Util/TemplateMatrix.hpp>

#include "I_RgbMatrix.hpp"


namespace Bt {
namespace Ui {

class Colorduino : public I_RgbMatrix
{
   public:
      enum {
         WIDTH = 8,
         HEIGHT = 8,
         BITS_PER_COLOR = 8
      };

      Colorduino();
      ~Colorduino();

      virtual void setPixel(uint8_t iX, uint8_t iY, Color iColor) ;
      virtual void fill(Color iColor) ;
      virtual void repaint();
   
   private:
      friend void timer2Callback();

   	  // Constructor to prohibit copy construction.
      Colorduino(const Colorduino&);

      // Operator= to prohibit copy assignment
      Colorduino& operator=(const Colorduino&);

      void initIo();
      void initLed();
      void initTimerIsr();

      void workcycle();

      void writeCurrentLine();
      void openCurrentLine();
      void incrementCurrentLine();
      void shiftOut(uint8_t iOneColor);


      typedef Color ScreenBuffer[8][8];

      Bt::Util::Singleton<Colorduino>::Instance mSingletonInstance;
      ScreenBuffer mScreens[2];
      uint8_t mWrite;
      uint8_t mRead;
      uint8_t mCurrentLine;

};

} // namespace Ui
} // namespace Bt

#endif // INC__Bt_Ui_Colorduino__hpp
