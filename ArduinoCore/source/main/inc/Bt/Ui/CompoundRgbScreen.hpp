//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::CompoundRgbScreen
//  
//*************************************************************************************************

#ifndef INC__Bt_Ui_CompoundRgbScreen__hpp
#define INC__Bt_Ui_CompoundRgbScreen__hpp

#include "Bt/Util/DynamicMatrix.hpp"
#include "Bt/Ui/I_RgbScreen.hpp"
#include "Bt/Util/DynamicArray.hpp"

namespace Bt {
namespace Ui {

class CompoundRgbScreen : public I_RgbScreen
{
   public:
      CompoundRgbScreen(const Util::I_Matrix<I_RgbScreen*>& iScreens);
      ~CompoundRgbScreen();

      virtual size_t width();
      virtual size_t height();

      virtual void setPixel(uint8_t iX, uint8_t iY, Color iColor);
      virtual void fill(Color iColor);
      virtual void repaint();
      virtual uint8_t numberOfSegments();
      virtual Color whiteBalance(uint8_t iSegment);
      virtual void setWhiteBalance(Color iColor, uint8_t iSegment);
      virtual void persistWhiteBalance(uint8_t iSegment);

   private:
   	  // Constructor to prohibit copy construction.
      CompoundRgbScreen(const CompoundRgbScreen&);

      // Operator= to prohibit copy assignment
      CompoundRgbScreen& operator=(const CompoundRgbScreen&);

      void getSegmentIndex(uint8_t iSegment, uint8_t& oIndex, uint8_t& oSubsegment);

      struct Index {
         Index(size_t iScreenIndex, size_t iPixelIndex) : mScreenIndex(iScreenIndex), mPixelIndex(iPixelIndex)  {
         }
         Index() : mScreenIndex(0), mPixelIndex(0)  {
         }
         size_t mScreenIndex;
         size_t mPixelIndex;
      };

      Util::DynamicMatrix<I_RgbScreen*> mScreens;

      Bt::Util::DynamicArray<Index> mRowIndex;
      Bt::Util::DynamicArray<Index> mColumnIndex;

};

} // namespace Ui
} // namespace Bt

#endif // INC__Bt_Ui_CompoundRgbScreen__hpp
