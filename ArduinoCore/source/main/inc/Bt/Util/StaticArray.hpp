//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::StaticArray
//  
//*************************************************************************************************

#ifndef INC__Bt_Util_StaticArray__hpp
#define INC__Bt_Util_StaticArray__hpp

#include <stdint.h>

namespace Bt {
namespace Util {

template<typename T, size_t SIZE>
class StaticArray {
   public:

      StaticArray()
      : mData() {
      }

      ~StaticArray() {
      }

      size_t size() const {
         return SIZE;
      }

      virtual const T& operator[](size_t iIndex) const {
         return mData[iIndex];
      }

      virtual T& operator[](size_t iIndex) {
         return mData[iIndex];
      }

   private:
      StaticArray(const StaticArray<T,SIZE>& iArray);
      StaticArray& operator=(const StaticArray& iArray);

      void copy(const StaticArray<T,SIZE>& iArray) {
         for (int i = 0; i < iArray.mSize; ++i) {
            mData[i] = iArray[i];
         }
      }

      T mData[SIZE];

};

} // namespace Util
} // namespace Bt

#endif // INC__Bt_Util_StaticArray__hpp
