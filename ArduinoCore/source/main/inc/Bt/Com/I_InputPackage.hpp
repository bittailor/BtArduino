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

      virtual I_InputPackage& operator>>(bool& oValue) = 0;
      virtual I_InputPackage& operator>>(int8_t& oValue) = 0;
      virtual I_InputPackage& operator>>(uint8_t& oValue) = 0;

};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_I_InputPackage__hpp
