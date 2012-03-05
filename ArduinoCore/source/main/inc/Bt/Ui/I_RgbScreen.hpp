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
#include <stddef.h>

#include "Bt/Ui/Color.hpp"


namespace Bt {
namespace Ui {

class I_RgbScreen {
   public:
      virtual ~I_RgbScreen() {}
      
      /** @return the width of this screen */
      virtual size_t width() = 0;

      /** @return the height of this screen */
      virtual size_t height() = 0;

      /**
       * Sets the color of a pixel on the screen buffer.
       * @param iX  the X coordinate
       * @param iY  the Y coordinate
       * @param iColor the color
       */
      virtual void setPixel(uint8_t iX, uint8_t iY, Color iColor) = 0;

      /**
       * Fills the hole screen buffer with a color;
       * @param iColor the color
       */
      virtual void fill(Color iColor) = 0;

      /**
       * Sends the screen buffer to the screen.
       */
      virtual void repaint() = 0;

      /** @returns the number of segments in this screen */
      virtual uint8_t numberOfSegments() = 0;

      /** @return white balance height for a segment of this screen */
      virtual Color whiteBalance(uint8_t iSegment) = 0;

      /**
       * Sets the white balance for a segment of the screen.
       * @param iColor the color used as white balance correction
       * @param iSegment the segment of the screen on which to set the white balance
       */
      virtual void setWhiteBalance(Color iColor, uint8_t iSegment) = 0;

      /**
       * Stores the current white balance in a persistent storage.
       * @param iSegment the segment of the screen on which to set the white balance
       */
      virtual void persistWhiteBalance(uint8_t iSegment) = 0;

};

} // namespace Ui
} // namespace Bt

#endif // INC__Bt_Ui_I_RgbScreen__hpp
