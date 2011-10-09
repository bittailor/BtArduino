//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::StaticMatrix
//  
//*************************************************************************************************

#ifndef INC__Bt_Util_StaticMatrix__hpp
#define INC__Bt_Util_StaticMatrix__hpp

#include "I_Matrix.hpp"

namespace Bt {
namespace Util {

template<typename T, uint8_t ROWS, uint8_t COLUMNS>
class StaticMatrix : public I_Matrix<T> {
   public:
      StaticMatrix()
      : mData() {
      }

      ~StaticMatrix() {
      }

      virtual uint8_t rows() const {
         return ROWS;
      }

      virtual uint8_t columns() const {
         return COLUMNS;
      }

      virtual const T& operator()(uint8_t iRow, uint8_t iColumn) const {
         // TODO Bt: range checks
         return mData[iRow][iColumn];
      }

      virtual T& operator()(uint8_t iRow, uint8_t iColumn) {
         // TODO Bt: range checks
         return mData[iRow][iColumn];
      }

   private:
      T mData[ROWS][COLUMNS];
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------


} // namespace Util
} // namespace Bt

#endif // INC__Bt_Util_StaticMatrix__hpp
