//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::StaticArrayTest
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include "Bt/Util/StaticArray.hpp"

namespace Bt {
namespace Util {

//-------------------------------------------------------------------------------------------------

TEST(StaticArrayTest, testConstructor) {
   const static size_t SIZE = 9;
   StaticArray<int,SIZE> array;
   EXPECT_EQ(SIZE,array.size());
   for (unsigned int i = 0; i < array.size() ; ++i) {
      EXPECT_EQ(0,array[i]);
   }
}

//-------------------------------------------------------------------------------------------------

TEST(StaticArrayTest, getAndSet) {
   StaticArray<int,12> array;
   for (unsigned int i = 0; i < array.size() ; ++i) {
      array[i] = i;
   }

   StaticArray<int,12>& constArray = array;

   for (unsigned int i = 0; i < constArray.size() ; ++i) {
      EXPECT_EQ(i,constArray[i]);
   }
}

//-------------------------------------------------------------------------------------------------

} // namespace Util
} // namespace Bt
