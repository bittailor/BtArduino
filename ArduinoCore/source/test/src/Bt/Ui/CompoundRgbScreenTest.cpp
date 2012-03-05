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
#include "Bt/Util/StaticMatrix.hpp"

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
      
      Bt::Util::StaticMatrix<I_RgbScreen*,2,2> init() {
         EXPECT_CALL(mScreen1, height()).WillRepeatedly(Return(8));
         EXPECT_CALL(mScreen1, width()).WillRepeatedly(Return(8));

         EXPECT_CALL(mScreen2, height()).WillRepeatedly(Return(8));
         EXPECT_CALL(mScreen2, width()).WillRepeatedly(Return(8));

         EXPECT_CALL(mScreen3, height()).WillRepeatedly(Return(8));
         EXPECT_CALL(mScreen3, width()).WillRepeatedly(Return(8));

         EXPECT_CALL(mScreen4, height()).WillRepeatedly(Return(8));
         EXPECT_CALL(mScreen4, width()).WillRepeatedly(Return(8));

         EXPECT_CALL(mScreen1, numberOfSegments()).WillRepeatedly(Return(1));
         EXPECT_CALL(mScreen2, numberOfSegments()).WillRepeatedly(Return(1));
         EXPECT_CALL(mScreen3, numberOfSegments()).WillRepeatedly(Return(1));
         EXPECT_CALL(mScreen4, numberOfSegments()).WillRepeatedly(Return(1));


         Bt::Util::StaticMatrix<I_RgbScreen*,2,2> screens;
         screens(0,0) = &mScreen1;
         screens(0,1) = &mScreen2;
         screens(1,0) = &mScreen3;
         screens(1,1) = &mScreen4;
         return screens;
      }

      virtual void SetUp() {
      }

      virtual void TearDown() {
         
      }

      Color mRed;
      RgbScreenGMock mScreen1;
      RgbScreenGMock mScreen2;
      RgbScreenGMock mScreen3;
      RgbScreenGMock mScreen4;
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

TEST_F(CompoundRgbScreenTest, numberOfSegments) {
   EXPECT_EQ(4,mScreen.numberOfSegments());
}

TEST_F(CompoundRgbScreenTest, setWhiteBalance_0) {
   Color color(1,2,3);
   EXPECT_CALL(mScreen1, setWhiteBalance(color,0)).Times(1);

   mScreen.setWhiteBalance(color,0);
}
TEST_F(CompoundRgbScreenTest, setWhiteBalance_1) {
   Color color(1,2,3);
   EXPECT_CALL(mScreen2, setWhiteBalance(color,0)).Times(1);

   mScreen.setWhiteBalance(color,1);
}

TEST_F(CompoundRgbScreenTest, setWhiteBalance_2) {
   Color color(1,2,3);
   EXPECT_CALL(mScreen3, setWhiteBalance(color,0)).Times(1);

   mScreen.setWhiteBalance(color,2);
}

TEST_F(CompoundRgbScreenTest, setWhiteBalance_3) {
   Color color(1,2,3);
   EXPECT_CALL(mScreen4, setWhiteBalance(color,0)).Times(1);

   mScreen.setWhiteBalance(color,3);
}

TEST_F(CompoundRgbScreenTest, whiteBalance_2) {
   Color color(33,22,11);
   EXPECT_CALL(mScreen3, whiteBalance(0)).WillOnce(Return(color));

   EXPECT_TRUE(color == mScreen.whiteBalance(2));
}

TEST_F(CompoundRgbScreenTest, persistWhiteBalance_1) {
   EXPECT_CALL(mScreen2, persistWhiteBalance(0)).Times(1);
   mScreen.persistWhiteBalance(1);
}





} // namespace Ui
} // namespace Bt
