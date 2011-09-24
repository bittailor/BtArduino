//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::SingletonTest
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include "Bt/Util/Singleton.hpp"

namespace Bt {
namespace Util {

namespace {

class JustAClass {
   public:
      explicit JustAClass(int iId) : mId(iId) {
      }

      const int mId;
   private:
      // noncopyable
      JustAClass(const JustAClass&);
      JustAClass& operator=(const JustAClass&);
};


} // namespace

//-------------------------------------------------------------------------------------------------

TEST(SingletonTest, invalid) {
   EXPECT_EQ(false,Singleton<JustAClass>::valid());
   ASSERT_EQ(0,Singleton<JustAClass>::instance());
}

//-------------------------------------------------------------------------------------------------

TEST(SingletonTest, instanceAssign) {
   int id = 876;
   JustAClass x(id);
   Singleton<JustAClass>::Instance xSingleton(x);
   EXPECT_EQ(true,Singleton<JustAClass>::valid());
   EXPECT_EQ(&x,Singleton<JustAClass>::instance());
}

//-------------------------------------------------------------------------------------------------

TEST(SingletonTest, instanceUnassign) {
   int id = 876;
   JustAClass x(id);
   {
      Singleton<JustAClass>::Instance xSingleton(x);
      EXPECT_EQ(true,Singleton<JustAClass>::valid());
   }
   EXPECT_EQ(false,Singleton<JustAClass>::valid());
   ASSERT_EQ(0,Singleton<JustAClass>::instance());
}

//-------------------------------------------------------------------------------------------------

TEST(SingletonTest, reassign) {
   int id1 = 876;
   JustAClass x1(id1);
   int id2 = 234;
   JustAClass x2(id2);
   int id3 = 555;
   JustAClass x3(id3);
   {
      Singleton<JustAClass>::Instance xSingleton1(x1);
      EXPECT_EQ(true,Singleton<JustAClass>::valid());
      EXPECT_EQ(&x1,Singleton<JustAClass>::instance());
      {
         Singleton<JustAClass>::Instance xSingleton2(x2);
         EXPECT_EQ(true,Singleton<JustAClass>::valid());
         EXPECT_EQ(&x2,Singleton<JustAClass>::instance());
         {
            Singleton<JustAClass>::Instance xSingleton3(x3);
            EXPECT_EQ(true,Singleton<JustAClass>::valid());
            EXPECT_EQ(&x3,Singleton<JustAClass>::instance());
         }
      }
   }
   EXPECT_EQ(false,Singleton<JustAClass>::valid());
   ASSERT_EQ(0,Singleton<JustAClass>::instance());
}

//-------------------------------------------------------------------------------------------------

} // namespace Util
} // namespace Bt
