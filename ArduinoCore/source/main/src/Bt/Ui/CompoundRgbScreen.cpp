//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::CompoundRgbScreen
//  
//*************************************************************************************************

#include "Bt/Ui/CompoundRgbScreen.hpp"

namespace Bt {
namespace Ui {

namespace {

size_t countRows(const Util::I_Matrix<I_RgbScreen*>& iScreens) {
   size_t rows = 0;
   for (int row = 0; row < iScreens.rows(); ++row) {
      rows += iScreens(row,0)->height();
   }
   return rows;
}

size_t countColumns(const Util::I_Matrix<I_RgbScreen*>& iScreens) {
   size_t columns = 0;
   for (int column = 0; column < iScreens.columns(); ++column) {
      columns += iScreens(0,column)->width();
   }
   return columns;
}

} // namespace

//-------------------------------------------------------------------------------------------------

CompoundRgbScreen::CompoundRgbScreen(const Util::I_Matrix<I_RgbScreen*>& iScreens)
: mScreens(iScreens), mRowIndex(countRows(iScreens)), mColumnIndex(countColumns(iScreens))  {
   {
      size_t yOffest = 0;
      for (size_t row = 0; row < mScreens.rows(); ++row) {
         for (size_t y = 0; y < mScreens(row,0)->height() ; ++y) {
            mRowIndex[y+yOffest].mScreenIndex = row;
            mRowIndex[y+yOffest].mPixelIndex = y;
         }
         yOffest += mScreens(row,0)->height();
      }
   }
   {
      size_t xOffest = 0;
      for (size_t column = 0; column < mScreens.columns(); ++column) {
         for (size_t x = 0; x < mScreens(0,column)->width() ; ++x) {
            mColumnIndex[x+xOffest].mScreenIndex = column;
            mColumnIndex[x+xOffest].mPixelIndex = x;
         }
         xOffest += mScreens(0,column)->width();
      }
   }
}

//-------------------------------------------------------------------------------------------------

CompoundRgbScreen::~CompoundRgbScreen() {
}

//-------------------------------------------------------------------------------------------------

size_t CompoundRgbScreen::width() {
   return mColumnIndex.size();
}

//-------------------------------------------------------------------------------------------------

size_t CompoundRgbScreen::height() {
   return mRowIndex.size();
}

//-------------------------------------------------------------------------------------------------

void CompoundRgbScreen::setPixel(uint8_t iX, uint8_t iY, Color iColor) {
   Index& x = mColumnIndex[iX];
   Index& y = mRowIndex[iY];
   mScreens(y.mScreenIndex,x.mScreenIndex)->setPixel(x.mPixelIndex,y.mPixelIndex,iColor);
}

//-------------------------------------------------------------------------------------------------

void CompoundRgbScreen::fill(Color iColor) {
   for (int row = 0; row < mScreens.rows(); ++row) {
      for (int column = 0; column < mScreens.columns(); ++column) {
         mScreens(row,column)->fill(iColor);
      }
   }
}

//-------------------------------------------------------------------------------------------------

void CompoundRgbScreen::repaint() {
   for (int row = 0; row < mScreens.rows(); ++row) {
      for (int column = 0; column < mScreens.columns(); ++column) {
         mScreens(row,column)->repaint();
      }
   }
}

//-------------------------------------------------------------------------------------------------

} // namespace Ui
} // namespace Bt
