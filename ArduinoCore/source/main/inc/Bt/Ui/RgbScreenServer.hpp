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

#include <Bt/Com/I_RequestServer.hpp>
#include <Bt/Util/Singleton.hpp>

namespace Bt {
namespace Ui {

class RgbScreenServer : public Com::I_RequestServer
{
   public:

      RgbScreenServer(I_RgbScreen& iScreen);
      ~RgbScreenServer();

      virtual void handleRequest(Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut) ;

   private:
   	  // Constructor to prohibit copy construction.
      RgbScreenServer(const RgbScreenServer&);

      // Operator= to prohibit copy assignment
      RgbScreenServer& operator=(const RgbScreenServer&);

      void setPixel(Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut);
      void fill(Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut);
      void repaint(Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut);
      void setWhiteBalance(Com::I_InputPackage& iIn, Com::I_OutputPackage& oOut);

      I_RgbScreen* mScreen;
};

} // namespace Ui
} // namespace Bt

#endif // INC__Bt_Ui_RgbScreenServer__hpp
