//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::RgbScreenProxyTest
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include "Bt/Ui/RgbScreenProxy.hpp"
#include "Bt/Com/RequestClientGMock.hpp"
#include "Bt/Com/StaticArrayPackageBuffer.hpp"
#include "Bt/Com/BinaryInputPackage.hpp"
#include "Bt/Com/BinaryOutputPackage.hpp"

using namespace ::testing;

namespace Bt {
namespace Ui {

class RgbScreenProxyTest : public ::testing::Test {
   
   protected:
      
      RgbScreenProxyTest()
      : mIn(mInBuffer), mOut(mOutBuffer), mRgbScreenProxy(mRequestClient) {

      }

      virtual void SetUp() {
      }

      virtual void TearDown() {
         
      }

      Com::StaticArrayPackageBuffer<20> mInBuffer;
      Com::StaticArrayPackageBuffer<20> mOutBuffer;

      Com::BinaryInputPackage mIn;
      Com::BinaryOutputPackage mOut;

      Com::RequestClientGMock mRequestClient;
      RgbScreenProxy mRgbScreenProxy;

};


TEST_F(RgbScreenProxyTest, setPixel) {
   uint8_t x = 7;
   uint8_t y = 6;
   Color color(60,70,80);

   EXPECT_CALL(mRequestClient,out()).WillRepeatedly(ReturnRef(mOut));
   EXPECT_CALL(mRequestClient,sendRequest()).Times(1);

   mRgbScreenProxy.setPixel(x,y,color);

   EXPECT_EQ(6,mOutBuffer.length());
   EXPECT_EQ(static_cast<uint8_t>(RgbScreenProxy::SET_PIXEL),mOutBuffer.raw()[0]);
   EXPECT_EQ(7,mOutBuffer.raw()[1]);
   EXPECT_EQ(6,mOutBuffer.raw()[2]);
   EXPECT_EQ(60,mOutBuffer.raw()[3]);
   EXPECT_EQ(70,mOutBuffer.raw()[4]);
   EXPECT_EQ(80,mOutBuffer.raw()[5]);

}

TEST_F(RgbScreenProxyTest, width) {
   uint8_t width = 9;

   EXPECT_CALL(mRequestClient,out()).WillRepeatedly(ReturnRef(mOut));
   EXPECT_CALL(mRequestClient,in()).WillRepeatedly(ReturnRef(mIn));
   EXPECT_CALL(mRequestClient,sendRequest()).Times(1);

   Com::BinaryOutputPackage out(mInBuffer);
   out << width;

   size_t widthResult = mRgbScreenProxy.width();

   EXPECT_EQ(1,mOutBuffer.length());
   EXPECT_EQ(static_cast<uint8_t>(RgbScreenProxy::WIDTH),mOutBuffer.raw()[0]);
   EXPECT_EQ(width,widthResult);

}


} // namespace Ui
} // namespace Bt
