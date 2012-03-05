//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::RemoteRgbScreenProtocol
//  
//*************************************************************************************************

#ifndef INC__Bt_Ui_RemoteRgbScreenProtocol__hpp
#define INC__Bt_Ui_RemoteRgbScreenProtocol__hpp

#include <stdint.h>
#include "Bt/Com/I_OutputPackage.hpp"
#include "Bt/Com/I_InputPackage.hpp"

namespace Bt {
namespace Ui {

class RemoteRgbScreenProtocol {
   public:
      enum Command {
         WIDTH,
         HEIGHT,
         SET_PIXEL,
         FILL,
         REPAINT,
         NUMBER_OF_SEGMENTS,
         WHITE_BALANCE,
         SET_WHITE_BALANCE,
         PERSIST_WHITE_BALANCE
      };
};

inline Bt::Com::I_OutputPackage& operator<< (Bt::Com::I_OutputPackage& i_raOut, RemoteRgbScreenProtocol::Command command) {
   i_raOut << static_cast<uint8_t>(command);
   return i_raOut;
}

} // namespace Ui
} // namespace Bt

#endif // INC__Bt_Ui_RemoteRgbScreenProtocol__hpp
