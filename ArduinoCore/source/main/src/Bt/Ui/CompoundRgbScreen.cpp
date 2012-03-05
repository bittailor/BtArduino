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

uint8_t CompoundRgbScreen::numberOfSegments() {
   uint8_t segments = 0;
   for (int row = 0; row < mScreens.rows(); ++row) {
      for (int column = 0; column < mScreens.columns(); ++column) {
         segments += mScreens(row,column)->numberOfSegments();
      }
   }
   return segments;
}

//-------------------------------------------------------------------------------------------------

Color CompoundRgbScreen::whiteBalance(uint8_t iSegment) {
   if (iSegment >= numberOfSegments()) {
      return Color();
   }

   uint8_t index;
   uint8_t subsegment;
   getSegmentIndex(iSegment,index,subsegment);

   return mScreens[index]->whiteBalance(subsegment);
}

//-------------------------------------------------------------------------------------------------

void CompoundRgbScreen::setWhiteBalance(Color iColor, uint8_t iSegment) {

   if (iSegment >= numberOfSegments()) {
      return;
   }

   uint8_t index;
   uint8_t subsegment;
   getSegmentIndex(iSegment,index,subsegment);

   mScreens[index]->setWhiteBalance(iColor,subsegment);
}

//-------------------------------------------------------------------------------------------------

void CompoundRgbScreen::persistWhiteBalance(uint8_t iSegment) {
   if (iSegment >= numberOfSegments()) {
      return;
   }

   uint8_t index;
   uint8_t subsegment;
   getSegmentIndex(iSegment,index,subsegment);

   mScreens[index]->persistWhiteBalance(subsegment);
}

//-------------------------------------------------------------------------------------------------

void CompoundRgbScreen::getSegmentIndex(uint8_t iSegment, uint8_t& oIndex, uint8_t& oSubsegment) {
   uint8_t size  = mScreens.rows()*mScreens.columns();
   uint8_t current = 0;
   for (int i = 0; i < (size - 1)  ; ++i) {
      uint8_t next = current + mScreens[i]->numberOfSegments();
      if ( next > iSegment) {
         oIndex = i;
         oSubsegment = iSegment - current;
         return;
      }
      current = next;
   }

   oIndex = size - 1;
   oSubsegment = iSegment - current;
}

//-------------------------------------------------------------------------------------------------

} // namespace Ui
} // namespace Bt
