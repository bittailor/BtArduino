//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Util::Logging
//  
//*************************************************************************************************

#ifndef INC__Bt_Util_Logging__hpp
#define INC__Bt_Util_Logging__hpp

#include "Bt/Util/Singleton.hpp"
#include "Bt/Util/I_Logger.hpp"

namespace Bt {
namespace Util {


#define BT_UTIL_LOG_ERROR( message ) \
   (*Singleton<I_Logger>::instance()) << message ;


} // namespace Util
} // namespace Bt

#endif // INC__Bt_Util_Logging__hpp
