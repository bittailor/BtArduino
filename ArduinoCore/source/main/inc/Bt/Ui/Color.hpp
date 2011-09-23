//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::Color
//  
//*************************************************************************************************

#ifndef INC__Bt_Ui_Color__hpp
#define INC__Bt_Ui_Color__hpp

#include <stdint.h>

namespace Bt {
namespace Ui {

class Color 
{
   public:
      Color()
      : mRed(0), mGreen(0), mBlue(0) {
      }

      Color(uint8_t iRed, uint8_t iGreen, uint8_t iBlue)
      : mRed(iRed), mGreen(iGreen), mBlue(iBlue) {
      }

      ~Color() {
      }

      uint8_t red() const {
         return mRed;
      }

      uint8_t green() const {
         return mGreen;
      }

      uint8_t blue() const {
         return mBlue;
      }

   private:
      uint8_t mRed;
      uint8_t mGreen;
      uint8_t mBlue;

};

} // namespace Ui
} // namespace Bt

#endif // INC__Bt_Ui_Color__hpp
