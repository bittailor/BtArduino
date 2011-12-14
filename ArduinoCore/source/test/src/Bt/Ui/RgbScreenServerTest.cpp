//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::RgbScreenServerTest
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include "Bt/Ui/RgbScreenServer.hpp"
#include "Bt/Ui/RgbScreenGMock.hpp"
#include "Bt/Ui/RgbScreenProxy.hpp"
#include "Bt/Com/InputPackageGMock.hpp"
#include "Bt/Com/OutputPackageGMock.hpp"
#include "Bt/Com/StaticArrayPackageBuffer.hpp"
#include "Bt/Com/BinaryInputPackage.hpp"
#include "Bt/Com/BinaryOutputPackage.hpp"

using namespace ::testing;

namespace Bt {
namespace Ui {

namespace {

   uint8_t asUInt8(int i) {
      return i;
   }

}

class RgbScreenServerTest : public ::testing::Test {
   
   protected:
      
      RgbScreenServerTest()
      : mIn(mInBuffer), mOut(mOutBuffer), mRgbScreenServer(mScreen)  {

      }

      virtual void SetUp() {
      }

      virtual void TearDown() {
         
      }

      StrictMock<Com::InputPackageGMock> mInMock;
      StrictMock<Com::OutputPackageGMock> mOutMock;

      Com::StaticArrayPackageBuffer<20> mInBuffer;
      Com::StaticArrayPackageBuffer<20> mOutBuffer;

      Com::BinaryInputPackage mIn;
      Com::BinaryOutputPackage mOut;

      RgbScreenGMock mScreen;
      RgbScreenServer mRgbScreenServer;

};

/*
TEST_F(RgbScreenServerTest, testSetPixelViaMockStreams) {
   Color color(60,70,80);


   EXPECT_CALL(mInMock, readUInt8())
      .WillOnce(Return(asUInt8(RgbScreenProxy::SET_PIXEL)))
      .WillOnce(Return(asUInt8(2)))
      .WillOnce(Return(asUInt8(3)))
      .WillOnce(Return(asUInt8(60)))
      .WillOnce(Return(asUInt8(70)))
      .WillOnce(Return(asUInt8(80)));

   EXPECT_CALL(mScreen,setPixel(2,3,color));

   mRgbScreenServer.handleRequest(mInMock,mOutMock);

}
*/

TEST_F(RgbScreenServerTest, testSetPixelViaBinaryStreams) {
   uint8_t command = RgbScreenProxy::SET_PIXEL;
   uint8_t x = 7;
   uint8_t y = 6;
   Color color(60,70,80);

   Com::BinaryOutputPackage out(mInBuffer);

   out << command << x << y << color;

   EXPECT_CALL(mScreen,setPixel(x,y,color));

   mRgbScreenServer.handleRequest(mIn,mOutMock);
}

TEST_F(RgbScreenServerTest, testWidthViaBinaryStreams) {
   uint8_t command = RgbScreenProxy::WIDTH;
   uint8_t width = 5;

   Com::BinaryOutputPackage out(mInBuffer);

   out << command;

   EXPECT_CALL(mScreen,width()).WillOnce(Return(width));

   mRgbScreenServer.handleRequest(mIn,mOut);

   EXPECT_EQ(1,mOutBuffer.length());
   EXPECT_EQ(width,mOutBuffer.raw()[0]);
}



} // namespace Ui
} // namespace Bt
