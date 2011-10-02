//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::CompoundRgbScreenTest
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include "Bt/Ui/CompoundRgbScreen.hpp"
#include "Bt/Ui/RgbScreenGMock.hpp"
#include "Bt/Util/TemplateMatrix.hpp"

using namespace ::testing;

namespace Bt {
namespace Ui {

namespace {

}

class CompoundRgbScreenTest : public ::testing::Test {
   
   protected:
      CompoundRgbScreenTest()
      : mRed(255,0,0),mScreen(init()) {

      }
      
      Bt::Util::TemplateMatrix<I_RgbScreen*,1,2> init() {
         EXPECT_CALL(mScreen1, height()).WillRepeatedly(Return(8));
         EXPECT_CALL(mScreen1, width()).WillRepeatedly(Return(8));

         EXPECT_CALL(mScreen2, height()).WillRepeatedly(Return(8));
         EXPECT_CALL(mScreen2, width()).WillRepeatedly(Return(8));

         Bt::Util::TemplateMatrix<I_RgbScreen*,1,2> screens;
         screens(0,0) = &mScreen1;
         screens(0,1) = &mScreen2;
         return screens;
      }

      virtual void SetUp() {
      }

      virtual void TearDown() {
         
      }

      Color mRed;
      RgbScreenGMock mScreen1;
      RgbScreenGMock mScreen2;
      CompoundRgbScreen mScreen;

};

TEST_F(CompoundRgbScreenTest, setPixel_15_7) {

   EXPECT_CALL(mScreen2, setPixel(7,7,mRed)).Times(1);
   mScreen.setPixel(15,7,mRed);
}

TEST_F(CompoundRgbScreenTest, setPixel_8_0) {
   EXPECT_CALL(mScreen2, setPixel(0,0,mRed)).Times(1);
   mScreen.setPixel(8,0,mRed);
}

TEST_F(CompoundRgbScreenTest, setPixel_12_4) {
   EXPECT_CALL(mScreen2, setPixel(4,4,mRed)).Times(1);
   mScreen.setPixel(12,4,mRed);
}

TEST_F(CompoundRgbScreenTest, setPixel_7_7) {
   EXPECT_CALL(mScreen1, setPixel(7,7,mRed)).Times(1);
   mScreen.setPixel(7,7,mRed);
}

TEST_F(CompoundRgbScreenTest, setPixel_0_0) {
   EXPECT_CALL(mScreen1, setPixel(0,0,mRed)).Times(1);
   mScreen.setPixel(0,0,mRed);
}

TEST_F(CompoundRgbScreenTest, setPixel_4_4) {
   EXPECT_CALL(mScreen1, setPixel(4,4,mRed)).Times(1);
   mScreen.setPixel(4,4,mRed);
}



} // namespace Ui
} // namespace Bt
