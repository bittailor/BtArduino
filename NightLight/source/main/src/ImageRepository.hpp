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


class ImageRepository 
{
   public:
      ImageRepository();
      ~ImageRepository();
   
   private:
   	  // Constructor to prohibit copy construction.
      ImageRepository(const ImageRepository&);

      // Operator= to prohibit copy assignment
      ImageRepository& operator=(const ImageRepository&);
};


#endif // INC__ImageRepository__hpp