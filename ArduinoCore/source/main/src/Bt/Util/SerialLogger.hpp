//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::SerialLogger
//  
//*************************************************************************************************

#ifndef INC__Bt_Util_SerialLogger__hpp
#define INC__Bt_Util_SerialLogger__hpp


#include "Bt/Util/I_Logger.hpp"

namespace Bt {
namespace Util {

class SerialLogger : public I_Logger
{
   public:
      SerialLogger();
      ~SerialLogger();

      virtual I_Logger& operator<<(I_Logger& (*pManuipulator)(I_Logger&)) = 0;
      virtual I_Logger& operator<<(const char* pCString) = 0;
      virtual I_Logger& operator<<(int pInteger) = 0;
   
   private:
   	  // Constructor to prohibit copy construction.
      SerialLogger(const SerialLogger&);

      // Operator= to prohibit copy assignment
      SerialLogger& operator=(const SerialLogger&);
};

} // namespace Util
} // namespace Bt

#endif // INC__Bt_Util_SerialLogger__hpp
