//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::DynamicMatrix
//  
//*************************************************************************************************

#ifndef INC__Bt_Util_DynamicMatrix__hpp
#define INC__Bt_Util_DynamicMatrix__hpp

#include <stddef.h>

#include "Bt/Util/I_Matrix.hpp"

namespace Bt {
namespace Util {

template <typename T>
class DynamicMatrix : public I_Matrix<T>
{
   public:
      DynamicMatrix (uint8_t iRows, uint8_t iColumns)
      : mRows(iRows), mColumns(iColumns){
         size_t rawSize = mRows * mColumns;
         mData = new T[rawSize];
         for (size_t i = 0 ; i < rawSize ; ++i) {
            mData[i] = T();
         }
      }

      DynamicMatrix (const I_Matrix<T>& iMatrix)
      : mRows(iMatrix.rows()), mColumns(iMatrix.columns()) {
         mData = new T[mRows * mColumns];
         copy(iMatrix);
      }

      DynamicMatrix(const DynamicMatrix& iMatrix)
      : mRows(iMatrix.rows()), mColumns(iMatrix.columns()) {
         size_t rawSize = mRows * mColumns;
         mData = new T[rawSize];
         copyRaw(iMatrix,rawSize);
      }

      ~DynamicMatrix() {
         delete [] mData;
      }

      DynamicMatrix& operator=(const DynamicMatrix& iMatrix) {
         T* old = mData;

         mRows = iMatrix.rows();
         mColumns = iMatrix.columns();
         size_t rawSize = mRows * mColumns;
         mData = new T[rawSize];
         copyRaw(iMatrix,rawSize);

         delete old;

         return *this;
      }

      DynamicMatrix& operator=(const I_Matrix<T>& iMatrix) {
         T* old = mData;
         mRows = iMatrix.rows();
         mColumns = iMatrix.columns();
         mData = new T[mRows * mColumns];
         copy(iMatrix);
         delete old;
         return *this;
      }

      virtual uint8_t rows() const {
         return mRows;
      }

      virtual uint8_t columns() const {
         return mColumns;
      }


      virtual const T& operator()(uint8_t iRow, uint8_t iColumn) const {
         return mData[iRow * mColumns + iColumn];
      }

      virtual T& operator()(uint8_t iRow, uint8_t iColumn) {
         return mData[iRow * mColumns + iColumn];
      }

      T& operator[](uint8_t iIndex) {
         return mData[iIndex];
      }

   private:

      void copy(const Util::I_Matrix<T>& iMatrix) {
         for (size_t row = 0 ; row < mRows ; ++row) {
            for (size_t column = 0 ; column < mColumns ; ++column) {
               (*this)(row,column) = iMatrix(row,column);
            }
         }
      }

      void copyRaw(const DynamicMatrix& iMatrix, size_t iRawSize) {
         for (size_t i = 0 ; i < iRawSize ; ++i) {
            mData[i] = iMatrix.mData[i];
         }
      }


      uint8_t mRows;
      uint8_t mColumns;
      T* mData;
};

} // namespace Util
} // namespace Bt

#endif // INC__Bt_Util_DynamicMatrix__hpp
