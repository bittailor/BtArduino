//*************************************************************************************************
//
//  BITTAILOR.CH - NightLight
//
//-------------------------------------------------------------------------------------------------
//
//  ImageRepository
//  
//*************************************************************************************************

#ifndef INC__ImageRepository__hpp
#define INC__ImageRepository__hpp

#include "Image.hpp"

class ImageRepository 
{
   public:
      static size_t size();
      static Image& getImage(size_t iIndex);

   private:
      // Constructor to prohibit construction.
      ImageRepository();
      ~ImageRepository();

   	  // Constructor to prohibit copy construction.
      ImageRepository(const ImageRepository&);

      // Operator= to prohibit copy assignment
      ImageRepository& operator=(const ImageRepository&);
};


#endif // INC__ImageRepository__hpp
