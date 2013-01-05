//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::VectorTest
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include <stddef.h>
#include "Bt/Util/Vector.hpp"

namespace Bt {
namespace Util {

namespace {

   class EmptyConstructor {

   };

   class OneArgConstructor {
      public:
         OneArgConstructor(int8_t iValue) : mValue(iValue) {
         }

         inline int8_t value() const {
            return mValue;
         }

      private:
         OneArgConstructor(const OneArgConstructor&);
         OneArgConstructor& operator=(const OneArgConstructor&);

         int8_t mValue;
   };

   class TwoArgConstructor {
      public:
         TwoArgConstructor(int8_t iValue, OneArgConstructor& iReference) : mValue(iValue), mReference(iReference) {
         }

         inline int8_t value() const {
            return mValue;
         }

         inline OneArgConstructor& reference() const {
            return mReference;
         }

      private:
         TwoArgConstructor(const TwoArgConstructor&);
         TwoArgConstructor& operator=(const TwoArgConstructor&);

         int8_t mValue;
         OneArgConstructor& mReference;
   };

   class FourArgConstructor {
      public:
         FourArgConstructor(int8_t iValue1,
                            int8_t iValue2,
                            int8_t iValue3,
                            int8_t iValue4)
         : mValue(iValue1){
         }

         inline int8_t value() const {
            return mValue;
         }



      private:
         FourArgConstructor(const TwoArgConstructor&);
         FourArgConstructor& operator=(const TwoArgConstructor&);

         int8_t mValue;

   };


}

class VectorTest : public ::testing::Test {
   
   protected:
      
      virtual void SetUp() {
      }

      virtual void TearDown() {
         
      }



};


TEST_F(VectorTest, Empty) {
   Vector<EmptyConstructor,5> mVector;
   mVector.pushBack();
   mVector.pushBack();
   mVector.pushBack();
}

TEST_F(VectorTest, OneArg) {
   const size_t SIZE = 5;
   Vector<OneArgConstructor,SIZE> mVector;
   for(size_t i = 0 ; i < SIZE ; i++) {
      mVector.pushBack(i);
   }

   for(size_t i = 0 ; i < SIZE ; i++) {
      EXPECT_EQ(i,mVector[i].value());
   }
}

TEST_F(VectorTest, Iterator) {
   const size_t SIZE = 5;
   Vector<OneArgConstructor,SIZE> mVector;
   for(size_t i = 0 ; i < SIZE ; i++) {
      mVector.pushBack(i);
   }

   size_t counter = 0;
   for (Vector<OneArgConstructor,SIZE>::Iterator iterator = mVector.begin(), end = mVector.end(); iterator != end; ++iterator) {
      EXPECT_EQ(counter , (size_t)iterator->value());
      counter++;
   }
   EXPECT_EQ(SIZE ,counter);
}

TEST_F(VectorTest, TwoArg) {
   const size_t SIZE = 5;
   Vector<OneArgConstructor,SIZE> mOneArgVector;
   Vector<TwoArgConstructor,SIZE> mTwoArgVector;

   for(size_t i = 0 ; i < SIZE ; i++) {
      mOneArgVector.pushBack(i);
      mTwoArgVector.pushBack<int8_t,OneArgConstructor&>(i,mOneArgVector[i]);

   }

   for(size_t i = 0 ; i < SIZE ; i++) {
      //EXPECT_EQ(i,mVector[i].value());
   }
}

TEST_F(VectorTest, FourArg) {
   const size_t SIZE = 5;
   Vector<FourArgConstructor,SIZE> mVector;
   for(size_t i = 0 ; i < SIZE ; i++) {
      mVector.pushBack(i,i,i,i);
   }

   for(size_t i = 0 ; i < SIZE ; i++) {
      EXPECT_EQ(i,mVector[i].value());
   }
}

} // namespace Util
} // namespace Bt
