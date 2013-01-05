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

      void draw(Bt::Ui::I_RgbScreen& pScreen);
   
   private:
      RawImage mRawData;
};


#endif // INC__Image__hpp
