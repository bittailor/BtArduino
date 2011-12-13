//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::TwoWireClientTest
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include "Bt/Com/TwoWireClient.hpp"
#include "Bt/Com/TwiGMock.hpp"

namespace Bt {
namespace Com {

class TwoWireClientTest : public ::testing::Test {
   
   protected:
      
      TwoWireClientTest()
      : mAddressOne(1), mAddressTwo(2), mTwoWireClientOne(init(),mAddressOne), mTwoWireClientTwo(mTwi,mAddressTwo) {

      }



      virtual void SetUp() {
      }

      virtual void TearDown() {

      }

      TwiGMock& init() {
         EXPECT_CALL(mTwi, init());
         return mTwi;
      }

      uint8_t mAddressOne;
      uint8_t mAddressTwo;
      TwiGMock mTwi;
      TwoWireClient<TwiGMock> mTwoWireClientOne;
      TwoWireClient<TwiGMock> mTwoWireClientTwo;

};


TEST_F(TwoWireClientTest, send) {
   // EXPECT_EQ(1,0);
}


} // namespace Com
} // namespace Bt
