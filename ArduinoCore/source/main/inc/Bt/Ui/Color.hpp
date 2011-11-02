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
#include "Bt/Com/I_OutputPackage.hpp"
#include "Bt/Com/I_InputPackage.hpp"

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

      explicit Color(Com::I_InputPackage& iIn)
      : mRed(0), mGreen(0), mBlue(0) {
         iIn >> mRed >> mGreen >> mBlue;
      }

      ~Color() {
      }

      void serialize(Com::I_OutputPackage& iOut) const {
         iOut << mRed << mGreen << mBlue;
      }

      bool operator==(const Color iColor) {
         return mRed == iColor.mRed && mGreen == iColor.mGreen && mBlue == iColor.mBlue;
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
