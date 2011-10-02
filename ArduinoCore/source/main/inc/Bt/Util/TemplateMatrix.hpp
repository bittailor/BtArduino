//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::TemplateMatrix
//  
//*************************************************************************************************

#ifndef INC__Bt_Util_TemplateMatrix__hpp
#define INC__Bt_Util_TemplateMatrix__hpp

#include "I_Matrix.hpp"

namespace Bt {
namespace Util {

template<typename T, uint8_t ROWS, uint8_t COLUMNS>
class TemplateMatrix : public I_Matrix<T> {
   public:
      TemplateMatrix()
      : mData() {
      }

      ~TemplateMatrix() {
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

#endif // INC__Bt_Util_TemplateMatrix__hpp
