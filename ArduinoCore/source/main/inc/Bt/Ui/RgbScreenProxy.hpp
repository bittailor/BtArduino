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
#include "Bt/Com/I_RequestClient.hpp"

namespace Bt {
namespace Ui {

class RgbScreenProxy : public I_RgbScreen
{
   public:

      RgbScreenProxy(Bt::Com::I_RequestClient& iClient);
      ~RgbScreenProxy();

      virtual size_t width();
      virtual size_t height();
   
      virtual void setPixel(uint8_t iX, uint8_t iY, Color iColor);
      virtual void fill(Color iColor);
      virtual void repaint();
      virtual uint8_t numberOfSegments();
      virtual Color whiteBalance(uint8_t iSegment);
      virtual void setWhiteBalance(Color iColor, uint8_t iSegment);
      virtual void persistWhiteBalance(uint8_t iSegment);

   private:
   	  // Constructor to prohibit copy construction.
      RgbScreenProxy(const RgbScreenProxy&);

      // Operator= to prohibit copy assignment
      RgbScreenProxy& operator=(const RgbScreenProxy&);

      Bt::Com::I_RequestClient* mClient;
      size_t mWidth;
      size_t mHeight;
      uint8_t mSegments;

};

} // namespace Ui
} // namespace Bt

#endif // INC__Bt_Ui_RgbScreenProxy__hpp
