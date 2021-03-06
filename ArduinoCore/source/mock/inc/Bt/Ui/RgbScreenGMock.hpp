//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::RgbScreenGMock
//  
//*************************************************************************************************

#ifndef INC__Bt_Ui_RgbScreenGMock__hpp
#define INC__Bt_Ui_RgbScreenGMock__hpp

#include <gmock/gmock.h>

#include "Bt/Ui/I_RgbScreen.hpp"

namespace Bt {
namespace Ui {

class RgbScreenGMock : public I_RgbScreen {
   public:

      MOCK_METHOD0(width,size_t ());
      MOCK_METHOD0(height,size_t ());
      MOCK_METHOD3(setPixel,void (uint8_t iX, uint8_t iY, Color iColor));
      MOCK_METHOD1(fill,void (Color iColor));
      MOCK_METHOD0(repaint,void ());
      MOCK_METHOD0(numberOfSegments,uint8_t ());
      MOCK_METHOD1(whiteBalance,Color (uint8_t iSegment));
      MOCK_METHOD2(setWhiteBalance,void (Color iColor, uint8_t iSegment));
      MOCK_METHOD1(persistWhiteBalance,void (uint8_t iSegment));

};

} // namespace Ui
} // namespace Bt

#endif // INC__Bt_Ui_RgbScreenGMock__hpp
