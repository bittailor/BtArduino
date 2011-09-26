//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::I_RgbScreen
//  
//*************************************************************************************************

#ifndef INC__Bt_Ui_I_RgbScreen__hpp
#define INC__Bt_Ui_I_RgbScreen__hpp

#include <stdint.h>

#include "Bt/Ui/Color.hpp"


namespace Bt {
namespace Ui {

class I_RgbScreen {
   public:
      virtual ~I_RgbScreen() {}
      
      /**
       * Sets the color of a pixel in the matrix.
       * @param iX  the X coordinate
       * @param iY  the Y coordinate
       * @param iColor the color
       */
      virtual void setPixel(uint8_t iX, uint8_t iY, Color iColor) = 0;

      /**
       * Fills the hole matrix with a color;
       * @param iColor the color
       */
      virtual void fill(Color iColor) = 0;

      /**
       * Sends the buffer to the screen.
       */
      virtual void repaint() = 0;
};

} // namespace Ui
} // namespace Bt

#endif // INC__Bt_Ui_I_RgbScreen__hpp
