//*************************************************************************************************
//
//  BITTAILOR.CH - NightLight
//
//-------------------------------------------------------------------------------------------------
//
//  Image
//  
//*************************************************************************************************

#ifndef INC__Image__hpp
#define INC__Image__hpp

#include <Bt/Ui/I_RgbScreen.hpp>


class Image 
{
   public:

      enum { SIZE = 16 };
      typedef const uint32_t (*RawImage)[SIZE];

      Image(const uint32_t iRawData[][SIZE]);
      ~Image();

      void draw(Bt::Ui::I_RgbScreen& iScreen);
      void draw(Bt::Ui::I_RgbScreen& iScreen, uint8_t iOffset, uint8_t iStart, uint8_t iSize);
   
   private:
      RawImage mRawData;
};


#endif // INC__Image__hpp
