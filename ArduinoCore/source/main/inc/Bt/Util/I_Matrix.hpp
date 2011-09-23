//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::I_Matrix
//  
//*************************************************************************************************

#ifndef INC__Bt_Util_I_Matrix__hpp
#define INC__Bt_Util_I_Matrix__hpp

#include <stdint.h>

namespace Bt {
namespace Util {

template<typename T>
class I_Matrix {
   public:
      virtual ~I_Matrix() {}
      
      virtual const T& operator()(uint8_t iX, uint8_t iY) const = 0;
      virtual T& operator()(uint8_t iX, uint8_t iY) = 0;

};

} // namespace Util
} // namespace Bt

#endif // INC__Bt_Util_I_Matrix__hpp
