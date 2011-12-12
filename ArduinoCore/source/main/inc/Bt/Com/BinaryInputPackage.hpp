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

      virtual I_PackageBuffer& buffer();

      virtual bool readBool();
      virtual int8_t readInt8();
      virtual uint8_t readUInt8();

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
