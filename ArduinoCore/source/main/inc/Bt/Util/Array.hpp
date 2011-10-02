//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::Array
//  
//*************************************************************************************************

#ifndef INC__Bt_Util_Array__hpp
#define INC__Bt_Util_Array__hpp

namespace Bt {
namespace Util {

template<typename T>
class Array {
   public:
      explicit Array(size_t iSize) : mSize(iSize) {
         if (mSize > 0) {
            mData = new T[mSize];
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

      ~Array() {
         delete mData;
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
      Array(const Array<T>& iArray);
      Array& operator=(const Array& iArray);

      void copy(const Array<T>& iArray) {
         for (int i = 0; i < iArray.mSize; ++i) {
            mData[i] = iArray[i];
         }
      }

      size_t mSize;
      T* mData;

};

} // namespace Util
} // namespace Bt

#endif // INC__Bt_Util_Array__hpp
