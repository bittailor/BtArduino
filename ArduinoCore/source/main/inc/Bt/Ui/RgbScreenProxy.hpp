//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::RgbScreenProxy
//  
//*************************************************************************************************

#ifndef INC__Bt_Ui_RgbScreenProxy__hpp
#define INC__Bt_Ui_RgbScreenProxy__hpp

#include "Bt/Ui/I_RgbScreen.hpp"

namespace Bt {
namespace Ui {

class RgbScreenProxy : public I_RgbScreen
{
   public:
      enum {
         SET_PIXEL,
         FILL,
         REPAINT
      };

      RgbScreenProxy(uint8_t iRemoteAddress);
      ~RgbScreenProxy();

      virtual size_t width();
      virtual size_t height();
   
      virtual void setPixel(uint8_t iX, uint8_t iY, Color iColor);
      virtual void fill(Color iColor);
      virtual void repaint();


   private:
   	  // Constructor to prohibit copy construction.
      RgbScreenProxy(const RgbScreenProxy&);

      // Operator= to prohibit copy assignment
      RgbScreenProxy& operator=(const RgbScreenProxy&);

      uint8_t mRemoteAddress;
};

} // namespace Ui
} // namespace Bt

#endif // INC__Bt_Ui_RgbScreenProxy__hpp
