//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::DynamicArray
//  
//*************************************************************************************************

#ifndef INC__Bt_Util_DynamicArray__hpp
#define INC__Bt_Util_DynamicArray__hpp

namespace Bt {
namespace Util {

template<typename T>
class DynamicArray {
   public:
      explicit DynamicArray(size_t iSize) : mSize(iSize) {
         if (mSize > 0) {
            mData = new T[mSize]();
            /*
            for (size_t i = 0; i < mSize; ++i) {
               mData[i] = T();
            }*/
         } else {
            mData = 0;
         }
      }

      /*
      Array(const Array<T>& iArray) : mSize(iArray.mSize) {
         if (mSize > 0) {
            mData = new T[mSize];
            copy(iArray);
         } else {
            mData = 0;
         }
      }

      Array& operator=(const Array& iArray) {
         T* old = mData;
         mSize = iArray.mSize;
         mData = new T[mSize];
         copy(iArray);
         delete old;
         return this;
      }
      */

      ~DynamicArray() {
         delete [] mData;
      }

      size_t size() const {
         return mSize;
      }

      virtual const T& operator[](size_t iIndex) const {
         return mData[iIndex];
      }

      virtual T& operator[](size_t iIndex) {
         return mData[iIndex];
      }

   private:
      DynamicArray(const DynamicArray<T>& iArray);
      DynamicArray& operator=(const DynamicArray& iArray);

      void copy(const DynamicArray<T>& iArray) {
         for (int i = 0; i < iArray.mSize; ++i) {
            mData[i] = iArray[i];
         }
      }

      size_t mSize;
      T* mData;

};

} // namespace Util
} // namespace Bt

#endif // INC__Bt_Util_DynamicArray__hpp
