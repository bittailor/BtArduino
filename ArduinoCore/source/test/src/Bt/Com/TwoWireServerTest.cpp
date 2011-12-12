//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::TwoWireServerTest
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include "Bt/Com/TwoWireServer.hpp"
#include "Bt/Com/RequestHandlerGMock.hpp"
#include "Bt/Com/TwiGMock.hpp"

using namespace ::testing;

namespace Bt {
namespace Com {



class TwoWireServerTest : public ::testing::Test {
   
   protected:
      TwoWireServerTest()
      : mAddress(2), mReceive(0), mTransmit(0), mTwoWireServer(init(),mAddress,mRequestHandler) {

      }

      virtual void SetUp() {
         ASSERT_TRUE(mReceive != 0);
         ASSERT_TRUE(mTransmit != 0);
      }

      virtual void TearDown() {
      }

      TwiGMock& init() {
         EXPECT_CALL(mTwi, setAddress(mAddress))
            .Times(1);
         EXPECT_CALL(mTwi, init())
            .Times(1);
         EXPECT_CALL(mTwi, attachSlaveRxEvent(_))
            .WillOnce(SaveArg<0>(&mReceive));
         EXPECT_CALL(mTwi, attachSlaveTxEvent(_))
                    .WillOnce(SaveArg<0>(&mTransmit));

         return mTwi;
      }

      uint8_t mAddress;
      RequestHandlerGMock mRequestHandler;
      TwiGMock mTwi;
      void (*mReceive)(uint8_t*, int);
      void (*mTransmit)();
      TwoWireServer<TwiGMock> mTwoWireServer;

};

static const int HANDLE_REQUEST_SIZE = 3;

void checkDoHandleRequest(Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut) {
   EXPECT_EQ(22,iIn.readUInt8());
   EXPECT_EQ(55,iIn.readUInt8());
   EXPECT_EQ(98,iIn.readUInt8());
   uint8_t value = 77;
   oOut.write(value);
   value = 23;
   oOut.write(value);
}

uint8_t checkAnswerSizeHandleRequest(const uint8_t* data, uint8_t length) {
   EXPECT_EQ(1,length);
   EXPECT_EQ(2,data[0]);
   return 0;
}

uint8_t checkAnswerHandleRequest(const uint8_t* data, uint8_t length) {
   EXPECT_EQ(2,length);
   EXPECT_EQ(77,data[0]);
   EXPECT_EQ(23,data[1]);
   return 0;
}

TEST_F(TwoWireServerTest, handleRequest) {
   uint8_t buffer[HANDLE_REQUEST_SIZE] = {22,55,98};

   EXPECT_CALL(mRequestHandler,handleRequest(_,_))
      .WillOnce(Invoke(checkDoHandleRequest));

   EXPECT_CALL(mTwi,transmit(_,1))
         .WillOnce(Invoke(checkAnswerSizeHandleRequest));

   EXPECT_CALL(mTwi,transmit(_,2))
         .WillOnce(Invoke(checkAnswerHandleRequest));


   mReceive(buffer,HANDLE_REQUEST_SIZE);
   mTransmit();
   mTransmit();
}


} // namespace Com
} // namespace Bt
