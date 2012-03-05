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

#include "Bt/Util/Singleton.hpp"
#include "Bt/Util/StaticMatrix.hpp"

#include "I_RgbScreen.hpp"


namespace Bt {
namespace Ui {

class Colorduino : public I_RgbScreen
{
   public:
      enum {
         WIDTH = 8,
         HEIGHT = 8,
         BITS_PER_BYTE = 8,
         MAX_WHITE_BALANCE = 63
      };

      explicit Colorduino(int iWhiteBalanceAddress);  //Color iWhiteBalance = Color(34,60,63));
      ~Colorduino();

      virtual size_t width();
      virtual size_t height();

      virtual void setPixel(uint8_t iX, uint8_t iY, Color iColor) ;
      virtual void fill(Color iColor) ;
      virtual void repaint();

      virtual uint8_t numberOfSegments();
      virtual Color whiteBalance(uint8_t iSegment);
      virtual void setWhiteBalance(Color iColor, uint8_t iSegment);
      virtual void persistWhiteBalance(uint8_t iSegment);
   
   private:
      friend void timer2Callback();

   	  // Constructor to prohibit copy construction.
      Colorduino(const Colorduino&);

      // Operator= to prohibit copy assignment
      Colorduino& operator=(const Colorduino&);

      void initIo();
      void initLed();
      void initTimerIsr();
      void initWhiteBalance();

      void workcycle();

      void openCurrentLine();
      void writeCurrentLine();
      void incrementCurrentLine();

      void shiftOut(uint8_t iOneColor, uint8_t numberOfBits = BITS_PER_BYTE);
      void shiftOut(const Color& iColor, uint8_t numberOfBits = BITS_PER_BYTE);

      Bt::Util::Singleton<Colorduino>::Instance mSingletonInstance;

      Bt::Util::StaticMatrix<Color,HEIGHT,WIDTH> mScreens[2];
      uint8_t mWrite;
      uint8_t mRead;
      uint8_t mCurrentLine;
      uint8_t* mWhiteBalanceAddress;
      Color mWhiteBalance;

};

} // namespace Ui
} // namespace Bt

#endif // INC__Bt_Ui_Colorduino__hpp
