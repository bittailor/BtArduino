//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::I_OutputPackage
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_I_OutputPackage__hpp
#define INC__Bt_Com_I_OutputPackage__hpp


#include <stdint.h>

#include "Bt/Com/I_PackageBuffer.hpp"

namespace Bt {
namespace Com {

class I_OutputPackage {
   public:
      virtual ~I_OutputPackage() {}

      virtual I_PackageBuffer& buffer() = 0;

      virtual I_OutputPackage& write(bool iValue) = 0;
      virtual I_OutputPackage& write(int8_t iValue) = 0;
      virtual I_OutputPackage& write(uint8_t iValue) = 0;


      // TODO do it with traits !
      I_OutputPackage& operator<<(bool iValue) {
         write(iValue);
         return *this;
      }

      I_OutputPackage& operator<<(int8_t iValue){
         write(iValue);
         return *this;
      }

      I_OutputPackage& operator<<(uint8_t iValue){
         write(iValue);
         return *this;
      }

      template<typename T>
      I_OutputPackage& operator<<(const T& iValue) {
         iValue.serialize(*this);
         return *this;
      }

};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_I_OutputPackage__hpp
