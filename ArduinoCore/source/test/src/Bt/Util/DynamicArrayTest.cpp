//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::DynamicArrayTest
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include "Bt/Util/DynamicArray.hpp"

#include "MemoryUsage.hpp"

namespace Bt {
namespace Util {

//-------------------------------------------------------------------------------------------------

TEST(DynamicArrayTest, testConstructor) {
   size_t size = 32;
   DynamicArray<int> array(size);
   EXPECT_EQ(size,array.size());
   for (unsigned int i = 0; i < array.size() ; ++i) {
      EXPECT_EQ(0,array[i]);
   }
}

//-------------------------------------------------------------------------------------------------

TEST(DynamicArrayTest, testMemory) {
   uint8_t size = 32;
   size_t memoryUsage = currentMemoryUsage();
   {
      DynamicArray<uint8_t> buffer(size);
   }
   EXPECT_EQ(currentMemoryUsage(),memoryUsage);
}

//-------------------------------------------------------------------------------------------------

TEST(DynamicArrayTest, testGetSet) {
   uint8_t size = 32;
   DynamicArray<uint8_t> buffer(size);
   for (unsigned int i = 0; i < buffer.size() ; ++i) {
      buffer[i] = i;
   }

   const DynamicArray<uint8_t>& constArray = buffer;

   for (unsigned int i = 0; i < constArray.size() ; ++i) {
      EXPECT_EQ(i,constArray[i]);
   }

}

//-------------------------------------------------------------------------------------------------

} // namespace Util
} // namespace Bt
