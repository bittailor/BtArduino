//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::TemplateMatrixTest
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include "Bt/Util/TemplateMatrix.hpp"

namespace Bt {
namespace Util {

//-------------------------------------------------------------------------------------------------

class TemplateMatrixTest : public ::testing::Test {
   
   protected:
      static const uint8_t X = 4;
      static const uint8_t Y = 6;


      virtual void SetUp() {
      }

      virtual void TearDown() {
         
      }

      TemplateMatrix<int,X,Y> mMatrix;

};

//-------------------------------------------------------------------------------------------------

TEST_F(TemplateMatrixTest, initialize) {
   for (uint8_t x = 0; x < X; ++x) {
      for (uint8_t y = 0; y < Y; ++y) {
         EXPECT_EQ(0,mMatrix(x,y));
      }
   }
}

//-------------------------------------------------------------------------------------------------

TEST_F(TemplateMatrixTest, getAndSet) {
   const int value = 564;
   mMatrix(2,3) = value;
   EXPECT_EQ(value,mMatrix(2,3));
}

//-------------------------------------------------------------------------------------------------

TEST_F(TemplateMatrixTest, assign) {

   mMatrix(1,1) = 11;
   mMatrix(2,2) = 22;
   mMatrix(1,3) = 13;

   TemplateMatrix<int,X,Y> otherMatrix;

   EXPECT_EQ(0,otherMatrix(1,1));

   otherMatrix = mMatrix;

   EXPECT_EQ(11,otherMatrix(1,1));
   EXPECT_EQ(22,otherMatrix(2,2));
   EXPECT_EQ(13,otherMatrix(1,3));

}

//-------------------------------------------------------------------------------------------------

} // namespace Util
} // namespace Bt
