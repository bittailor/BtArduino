//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::BinaryOutputPackage
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_BinaryOutputPackage__hpp
#define INC__Bt_Com_BinaryOutputPackage__hpp

#include "Bt/Com/I_OutputPackage.hpp"
#include "Bt/Com/I_PackageBuffer.hpp"

namespace Bt {
namespace Com {

class BinaryOutputPackage : public I_OutputPackage
{
   public:
      BinaryOutputPackage(I_PackageBuffer& iBuffer);
      ~BinaryOutputPackage();

      virtual I_PackageBuffer& buffer();

      virtual I_OutputPackage& write(bool iValue);
      virtual I_OutputPackage& write(int8_t iValue);
      virtual I_OutputPackage& write(uint8_t iValue);
   
   private:
   	  // Constructor to prohibit copy construction.
      BinaryOutputPackage(const BinaryOutputPackage&);

      // Operator= to prohibit copy assignment
      BinaryOutputPackage& operator=(const BinaryOutputPackage&);

      I_PackageBuffer* mBuffer;
};

} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_BinaryOutputPackage__hpp
