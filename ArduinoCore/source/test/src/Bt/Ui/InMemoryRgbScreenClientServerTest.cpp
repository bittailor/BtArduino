//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::InMemoryRgbScreenClientServerTest
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include "Bt/Ui/RgbScreenGMock.hpp"
#include "Bt/Ui/RgbScreenServer.hpp"
#include "Bt/Ui/RgbScreenProxy.hpp"
#include "Bt/Com/InMemoryClientServer.hpp"

using namespace testing;

namespace Bt {
namespace Ui {

class InMemoryRgbScreenClientServerTest : public ::testing::Test {
   
   protected:
      
      InMemoryRgbScreenClientServerTest()
      : mServer(mScreen), mInMemoryConnection(mServer), mProxy(mInMemoryConnection) {

      }

      virtual void SetUp() {
      }

      virtual void TearDown() {
         
      }

      RgbScreenGMock mScreen;
      RgbScreenServer mServer;
      Com::InMemoryClientServer mInMemoryConnection;
      RgbScreenProxy mProxy;

};


TEST_F(InMemoryRgbScreenClientServerTest, setPixel) {
   uint8_t x = 2;
   uint8_t y = 3;
   Color color(77,66,55);

   EXPECT_CALL(mScreen,setPixel(x,y,color));

   mProxy.setPixel(x,y,color);
}

TEST_F(InMemoryRgbScreenClientServerTest, setWhiteBalance) {
   uint8_t segment = 2;
   Color color(98,65,43);

   EXPECT_CALL(mScreen,setWhiteBalance(color,segment));

   mProxy.setWhiteBalance(color,segment);
}

TEST_F(InMemoryRgbScreenClientServerTest, whiteBalance) {
   uint8_t segment = 3;
   Color color(12,13,14);

   EXPECT_CALL(mScreen,whiteBalance(segment)).WillOnce(Return(color));

   Color returnColor = mProxy.whiteBalance(segment);
   EXPECT_TRUE(color == returnColor);
}


} // namespace Ui
} // namespace Bt
