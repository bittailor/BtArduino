//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::Buffer
//  
//*************************************************************************************************

#ifndef INC__Bt_Util_Buffer__hpp
#define INC__Bt_Util_Buffer__hpp

namespace Bt {
namespace Util {

template<typename T>
class Buffer {
   public:
      explicit Buffer(size_t iSize) : mSize(iSize) {
         mData = new T[iSize];
      }

      ~Buffer() {
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

      ~Buffer() {}
   private:
      size_t mSize;
      T* mData;

};

} // namespace Util
} // namespace Bt

#endif // INC__Bt_Util_Buffer__hpp
