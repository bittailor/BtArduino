//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::DynamicMatrixTest
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include "Bt/Util/DynamicMatrix.hpp"
#include "Bt/Util/StaticMatrix.hpp"

#include "MemoryUsage.hpp"

namespace Bt {
namespace Util {

namespace {

template<typename T>
void fill(I_Matrix<T>& iMatrix) {
   for (int row = 0 ; row < iMatrix.rows() ; ++row) {
      for (int column = 0 ; column < iMatrix.columns() ; ++column) {
         iMatrix(row,column) = row * 10 + column;
      }
   }
}

template<typename T>
void expectEqual(I_Matrix<T>& iExpected, I_Matrix<T>& iActual) {
   ASSERT_EQ(iExpected.rows(),iActual.rows());
   ASSERT_EQ(iExpected.columns(),iActual.columns());
   for (int row = 0 ; row < iExpected.rows() ; ++row) {
      for (int column = 0 ; column < iExpected.columns() ; ++column) {
         EXPECT_EQ(iExpected(row,column),iActual(row,column));
      }
   }
}

} // namespace

//-------------------------------------------------------------------------------------------------

TEST(DynamicMatrixTest, createAndDelete) {
   size_t memoryUsage = currentMemoryUsage();
   {
      DynamicMatrix<int> matrix(3,4);
   }
   EXPECT_EQ(currentMemoryUsage(),memoryUsage);
}

//-------------------------------------------------------------------------------------------------

TEST(DynamicMatrixTest, initialize) {
   DynamicMatrix<int> matrix(5,3);
   const DynamicMatrix<int>& constMatrix = matrix;
   for (uint8_t row = 0 ; row < constMatrix.rows() ; ++row) {
      for (uint8_t column = 0 ; column < constMatrix.columns() ; ++column) {
         EXPECT_EQ(0,constMatrix(row,column));
      }
   }
}

//-------------------------------------------------------------------------------------------------

TEST(DynamicMatrixTest, getAndSet) {
   int value1 = 86;
   int value2 = 3456;
   DynamicMatrix<int> matrix(3,8);

   matrix(2,6) = value1;
   matrix(0,4) = value2;

   EXPECT_EQ(0,matrix(0,0));
   EXPECT_EQ(value1,matrix(2,6));
   EXPECT_EQ(value2,matrix(0,4));
   EXPECT_EQ(0,matrix(2,7));
}

//-------------------------------------------------------------------------------------------------

TEST(DynamicMatrixTest, copy) {
   size_t memoryUsage = currentMemoryUsage();
   {
      DynamicMatrix<int> matrix(5,8);
      fill(matrix);
      DynamicMatrix<int> copy(matrix);
      EXPECT_EQ(45,copy(4,5));

      expectEqual(matrix,copy);

      matrix(4,5) = 99;
      EXPECT_EQ(99,matrix(4,5));
      EXPECT_EQ(45,copy(4,5));

      copy(2,7) = 11;
      EXPECT_EQ(11,copy(2,7));
      EXPECT_EQ(27,matrix(2,7));
   }
   EXPECT_EQ(currentMemoryUsage(),memoryUsage);
}

//-------------------------------------------------------------------------------------------------

TEST(DynamicMatrixTest, copyViaInterface) {
   size_t memoryUsage = currentMemoryUsage();
   {
      StaticMatrix<int,5,8> matrix;
      fill(matrix);
      DynamicMatrix<int> copy(matrix);
      EXPECT_EQ(45,matrix(4,5));
      EXPECT_EQ(45,copy(4,5));

      expectEqual(matrix,copy);

      matrix(4,5) = 99;
      EXPECT_EQ(99,matrix(4,5));
      EXPECT_EQ(45,copy(4,5));

      copy(2,7) = 11;
      EXPECT_EQ(11,copy(2,7));
      EXPECT_EQ(27,matrix(2,7));
   }
   EXPECT_EQ(currentMemoryUsage(),memoryUsage);
}

//-------------------------------------------------------------------------------------------------

TEST(DynamicMatrixTest, assignViaInterface) {
   size_t memoryUsage = currentMemoryUsage();
   {
      StaticMatrix<int,5,8> matrix;
      fill(matrix);
      DynamicMatrix<int> copy(2,3);

      copy = matrix;

      ASSERT_EQ(matrix.rows(),copy.rows());
      ASSERT_EQ(matrix.columns(),copy.columns());

      EXPECT_EQ(45,matrix(4,5));
      EXPECT_EQ(45,copy(4,5));

      expectEqual(matrix,copy);

      matrix(4,5) = 99;
      EXPECT_EQ(99,matrix(4,5));
      EXPECT_EQ(45,copy(4,5));

      copy(1,2) = 11;
      EXPECT_EQ(11,copy(1,2));
      EXPECT_EQ(12,matrix(1,2));
   }
   EXPECT_EQ(currentMemoryUsage(),memoryUsage);
}

//-------------------------------------------------------------------------------------------------

TEST(DynamicMatrixTest, assign) {
   size_t memoryUsage = currentMemoryUsage();
   {
      DynamicMatrix<int> matrix(5,8);
      fill(matrix);
      DynamicMatrix<int> copy(2,3);

      copy = matrix;

      ASSERT_EQ(matrix.rows(),copy.rows());
      ASSERT_EQ(matrix.columns(),copy.columns());

      EXPECT_EQ(45,matrix(4,5));
      EXPECT_EQ(45,copy(4,5));

      expectEqual(matrix,copy);

      matrix(4,5) = 99;
      EXPECT_EQ(99,matrix(4,5));
      EXPECT_EQ(45,copy(4,5));

      copy(1,2) = 11;
      EXPECT_EQ(11,copy(1,2));
      EXPECT_EQ(12,matrix(1,2));
   }
   EXPECT_EQ(currentMemoryUsage(),memoryUsage);
}

//-------------------------------------------------------------------------------------------------

} // namespace Util
} // namespace Bt
