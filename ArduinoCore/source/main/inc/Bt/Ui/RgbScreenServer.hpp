//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::RgbScreenServer
//  
//*************************************************************************************************

#ifndef INC__Bt_Ui_RgbScreenServer__hpp
#define INC__Bt_Ui_RgbScreenServer__hpp

#include "Bt/Ui/I_RgbScreen.hpp"
#include <Bt/Util/Singleton.hpp>

namespace Bt {
namespace Ui {

class RgbScreenServer
{
   public:

      RgbScreenServer(I_RgbScreen& iScreen);
      ~RgbScreenServer();

      void receive(int iNumberOfBytes);

   private:
   	  // Constructor to prohibit copy construction.
      RgbScreenServer(const RgbScreenServer&);

      // Operator= to prohibit copy assignment
      RgbScreenServer& operator=(const RgbScreenServer&);

      void setPixel(uint8_t iData[]);
      void fill(uint8_t iData[]);
      void repaint(uint8_t iData[]);


      I_RgbScreen& mScreen;
      Bt::Util::Singleton<RgbScreenServer>::Instance mSingletonInstance;
};

} // namespace Ui
} // namespace Bt

#endif // INC__Bt_Ui_RgbScreenServer__hpp
