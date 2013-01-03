//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Io::I_RawInput
//  
//*************************************************************************************************

#ifndef INC__Bt_Io_I_RawInput__hpp
#define INC__Bt_Io_I_RawInput__hpp

namespace Bt {
namespace Io {

template<typename T>
class I_RawInput {
   public:
      virtual ~I_RawInput() {}
      
      virtual T read() = 0;
};

} // namespace Io
} // namespace Bt

#endif // INC__Bt_Io_I_RawInput__hpp
