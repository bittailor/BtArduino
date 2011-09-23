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

template<typename T, uint8_t X, uint8_t Y>
class TemplateMatrix : public I_Matrix<T> {
   public:
      TemplateMatrix()
      : mData() {

      }

      virtual const T& operator()(uint8_t iX, uint8_t iY) const {
         return mData[iX][iY];
      }

      virtual T& operator()(uint8_t iX, uint8_t iY) {
         return mData[iX][iY];
      }

      ~TemplateMatrix() {}

   private:
      T mData[X][Y];
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------


} // namespace Util
} // namespace Bt

#endif // INC__Bt_Util_TemplateMatrix__hpp
