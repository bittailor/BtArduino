//*************************************************************************************************
//
//  BITTAILOR.CH - NightLight
//
//-------------------------------------------------------------------------------------------------
//
//  Image
//  
//*************************************************************************************************

#include "Image.hpp"

#include <avr/pgmspace.h>

#include "Settings.hpp"

//-------------------------------------------------------------------------------------------------

Image::Image(const uint32_t iRawData[][SIZE]) : mRawData(iRawData) {

}

//-------------------------------------------------------------------------------------------------

Image::~Image() {

}

//-------------------------------------------------------------------------------------------------



void Image::draw(Bt::Ui::I_RgbScreen& iScreen) {
   for(uint8_t x = 0; x < SIZE ; x++) {
      for(uint8_t y = 0; y < SIZE ; y++) {
         uint32_t rgb = pgm_read_dword(&(mRawData[x][y]));
         Bt::Ui::Color color(rgb);
         iScreen.setPixel(x,y,Bt::Ui::Color(color.red()/IMAGE_DIM_FACTOR,
                                            color.green()/IMAGE_DIM_FACTOR,
                                            color.blue()/IMAGE_DIM_FACTOR));
      }
   }
}

//-------------------------------------------------------------------------------------------------

void Image::draw(Bt::Ui::I_RgbScreen& iScreen, uint8_t iOffset, uint8_t iStart, uint8_t iSize) {
   for(uint8_t x = iStart; x < iStart+iSize ; x++) {
      for(uint8_t y = 0; y < SIZE ; y++) {
         uint32_t rgb = pgm_read_dword(&(mRawData[x][y]));
         Bt::Ui::Color color(rgb);
         iScreen.setPixel((x - iStart) + iOffset,y,Bt::Ui::Color(color.red()/IMAGE_DIM_FACTOR,
                                                                 color.green()/IMAGE_DIM_FACTOR,
                                                                 color.blue()/IMAGE_DIM_FACTOR));
      }
   }
}

//-------------------------------------------------------------------------------------------------

