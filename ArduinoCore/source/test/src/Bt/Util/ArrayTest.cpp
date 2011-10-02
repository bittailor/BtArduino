//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::ArrayTest
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include "Bt/Util/Array.hpp"

#include "MemoryUsage.hpp"

namespace Bt {
namespace Util {

//-------------------------------------------------------------------------------------------------

TEST(ArrayTest, testConstructor) {
   uint8_t size = 32;
   Array<uint8_t> buffer(size);
   EXPECT_EQ(size,buffer.size());
}

//-------------------------------------------------------------------------------------------------

TEST(ArrayTest, testMemory) {
   uint8_t size = 32;
   size_t memoryUsage = currentMemoryUsage();
   {
      Array<uint8_t> buffer(size);
   }
   EXPECT_EQ(currentMemoryUsage(),memoryUsage);
}

//-------------------------------------------------------------------------------------------------

TEST(ArrayTest, testGetSet) {
   uint8_t size = 32;
   Array<uint8_t> buffer(size);
   for (unsigned int i = 0; i < buffer.size() ; ++i) {
      buffer[i] = i;
   }

   const Array<uint8_t>& constArray = buffer;

   for (unsigned int i = 0; i < constArray.size() ; ++i) {
      EXPECT_EQ(i,constArray[i]);
   }

}

//-------------------------------------------------------------------------------------------------

} // namespace Util
} // namespace Bt
