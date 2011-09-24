//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::CompileDummy
//  
//*************************************************************************************************

#ifndef INC__Bt_Util_CompileDummy__hpp
#define INC__Bt_Util_CompileDummy__hpp

namespace Bt {
namespace Util {

class CompileDummy 
{
   public:
      CompileDummy();
      ~CompileDummy();
   
   private:
   	  // Constructor to prohibit copy construction.
      CompileDummy(const CompileDummy&);

      // Operator= to prohibit copy assignment
      CompileDummy& operator=(const CompileDummy&);
};

} // namespace Util
} // namespace Bt

#endif // INC__Bt_Util_CompileDummy__hpp