//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::Vector
//  
//*************************************************************************************************

#ifndef INC__Bt_Util_Vector__hpp
#define INC__Bt_Util_Vector__hpp

#include <stddef.h>

namespace Bt {
namespace Util {

template <typename T, size_t Capacity>
class Vector 
{
   public:

      typedef T* Iterator;

      Vector() : mSize(0) {

      }

      ~Vector() {
//         for(size_t i = 0 ; i < mSize ; i++) {
//            d
//         }
      }

      inline size_t capacity() {
         return Capacity;
      }

      void pushBack() {
         new (mRawMemory + offset(mSize)) T();
         mSize++;
      }

      template<typename Arg1>
      void pushBack(Arg1 iArg1) {
         new (mRawMemory + offset(mSize)) T(iArg1);
         mSize++;
      }

      template<typename Arg1, typename Arg2>
      void pushBack(Arg1 iArg1, Arg2 iArg2) {
         new (mRawMemory + offset(mSize)) T(iArg1, iArg2);
         mSize++;
      }

      template<typename Arg1, typename Arg2, typename Arg3>
      void pushBack(Arg1 iArg1, Arg2 iArg2, Arg3 iArg3) {
         new (mRawMemory + offset(mSize)) T(iArg1, iArg2, iArg3);
         mSize++;
      }

      template<typename Arg1, typename Arg2, typename Arg3, typename Arg4>
      void pushBack(Arg1 iArg1, Arg2 iArg2, Arg3 iArg3, Arg4 iArg4) {
         new (mRawMemory + offset(mSize)) T(iArg1, iArg2, iArg3, iArg4);
         mSize++;
      }

      T& operator[](size_t iIndex) {
         return ((T*)mRawMemory)[iIndex];
      }

      const T& operator[](size_t iIndex) const {
         return ((T*)mRawMemory)[iIndex];
      }

      inline Iterator begin() {
         return ((T*)mRawMemory);
      }

      Iterator end() {
         return ((T*)mRawMemory) + mSize;
      }


   private:
   	  // Constructor to prohibit copy construction.
      Vector(const Vector&);

      // Operator= to prohibit copy assignment
      Vector& operator=(const Vector&);

      inline size_t offset(size_t iIndex) {
         return iIndex * sizeof(T);
      }

      char mRawMemory[sizeof(T)*Capacity];

      size_t mSize;
};

} // namespace Util
} // namespace Bt

#endif // INC__Bt_Util_Vector__hpp
