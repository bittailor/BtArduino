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

      Image(const uint32_t iRawData[][SIZE]);
      ~Image();

      void draw(Bt::Ui::I_RgbScreen& pScreen);
   
   private:
   	  // Constructor to prohibit copy construction.
      Image(const Image&);

      // Operator= to prohibit copy assignment
      Image& operator=(const Image&);

      const uint32_t (*mRawData)[16];
      //const uint32_t mRawData[][SIZE];
};


#endif // INC__Image__hpp
