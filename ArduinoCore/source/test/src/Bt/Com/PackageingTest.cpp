//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::PackageingTest
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include "Bt/Com/StaticArrayPackageBuffer.hpp"
#include "Bt/Com/BinaryOutputPackage.hpp"
#include "Bt/Com/BinaryInputPackage.hpp"


namespace Bt {
namespace Com {

namespace {

   class JustAClass {
      public:
         JustAClass()
         : mUInt8(0), mInt8(0),mBool(false) {
         }

         JustAClass(uint8_t iUInt8, int8_t iInt8, bool iBool)
         : mUInt8(iUInt8), mInt8(iInt8),mBool(iBool) {
         }

         uint8_t mUInt8;
         int8_t mInt8;
         bool mBool;
   };

   Com::I_OutputPackage& operator<<(Com::I_OutputPackage& iPackage, const JustAClass& iObject) {
      iPackage << iObject.mUInt8 << iObject.mInt8 << iObject.mBool;
      return iPackage;
   }

   Com::I_InputPackage& operator>>(Com::I_InputPackage& iPackage, JustAClass& iObject) {
      iPackage >> iObject.mUInt8 >>  iObject.mInt8 >> iObject.mBool;
      return iPackage;
   }

   void check(uint8_t iUInt8, int8_t iInt8, bool iBool) {
      StaticArrayPackageBuffer<20> buffer;
      {
         BinaryOutputPackage out(buffer);
         JustAClass object(iUInt8,iInt8,iBool);
         out << object;
      }

      {
         BinaryInputPackage in(buffer);
         JustAClass object;
         in >> object;
         EXPECT_EQ(iUInt8,object.mUInt8);
         EXPECT_EQ(iInt8,object.mInt8);
         EXPECT_EQ(iBool,object.mBool);
      }
   }

}

TEST(PackageingTest, inAndOutOne) {
   check(255,-1,true);
}

TEST(PackageingTest, inAndOutTwo) {
   check(1,127,false);
}

TEST(PackageingTest, inAndOutThree) {
   check(128,-128,true);
}


} // namespace Com
} // namespace Bt
