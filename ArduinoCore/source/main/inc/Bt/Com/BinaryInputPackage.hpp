//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::BinaryInputPackage
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_BinaryInputPackage__hpp
#define INC__Bt_Com_BinaryInputPackage__hpp

#include "Bt/Com/I_InputPackage.hpp"
#include "Bt/Com/I_PackageBuffer.hpp"

namespace Bt {
namespace Com {

class BinaryInputPackage : public I_InputPackage
{
   public:
      BinaryInputPackage(I_PackageBuffer& iBuffer);
      ~BinaryInputPackage();

      virtual I_InputPackage& operator>>(bool& oValue);
      virtual I_InputPackage& operator>>(int8_t& oValue);
      virtual I_InputPackage& operator>>(uint8_t& oValue);
   
   private:
   	  // Constructor to prohibit copy construction.
      BinaryInputPackage(const BinaryInputPackage&);

      // Operator= to prohibit copy assignment
      BinaryInputPackage& operator=(const BinaryInputPackage&);

      I_PackageBuffer* mBuffer;
};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_BinaryInputPackage__hpp
