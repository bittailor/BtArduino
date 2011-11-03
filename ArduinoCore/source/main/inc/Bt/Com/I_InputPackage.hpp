//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::I_InputPackage
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_I_InputPackage__hpp
#define INC__Bt_Com_I_InputPackage__hpp


#include <stdint.h>

namespace Bt {
namespace Com {

class I_InputPackage {
   public:
      virtual ~I_InputPackage() {}

      virtual bool readBool() = 0;
      virtual int8_t readInt8() = 0;
      virtual uint8_t readUInt8() = 0;

      // TODO do it with traits !
      I_InputPackage& operator>>(bool& oValue) {
         oValue = readBool();
         return *this;
      }

      I_InputPackage& operator>>(int8_t& oValue) {
         oValue = readInt8();
         return *this;
      }

      I_InputPackage& operator>>(uint8_t& oValue) {
         oValue = readUInt8();
         return *this;
      }

};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_I_InputPackage__hpp
