//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::BufferTest
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include "Bt/Util/Buffer.hpp"

#include "MemoryUsage.hpp"

namespace Bt {
namespace Util {


TEST(BufferTest, testConstructor) {
   uint8_t size = 32;
   Buffer<uint8_t> buffer(size);
   EXPECT_EQ(size,buffer.size());
}

TEST(BufferTest, testMemory) {
   uint8_t size = 32;
   size_t memoryUsage = currentMemoryUsage();
   {
      Buffer<uint8_t> buffer(size);
   }
   EXPECT_EQ(currentMemoryUsage(),memoryUsage);
}

TEST(BufferTest, testGetSet) {
   uint8_t size = 32;
   Buffer<uint8_t> buffer(size);
   for (unsigned int i = 0; i < buffer.size() ; ++i) {
      buffer[i] = i;
   }

   const Buffer<uint8_t>& constBuffer = buffer;

   for (unsigned int i = 0; i < constBuffer.size() ; ++i) {
      EXPECT_EQ(i,constBuffer[i]);
   }

}


} // namespace Util
} // namespace Bt
