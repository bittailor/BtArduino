//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  MemoryUsage
//  
//*************************************************************************************************

#include "MemoryUsage.hpp"


namespace {
   const static size_t MARKER_SIZE = sizeof(size_t);

   int sCurrentUsage = 0;

   void* checkedMalloc(size_t iSize) {
      size_t* memory = static_cast<size_t*>(malloc(iSize+MARKER_SIZE));

      if (memory == 0) {
         return memory;
      }

      sCurrentUsage += iSize;
      *memory = iSize;
      memory++;
      return memory;
   }

   void checkedFree(void* iPointer)
   {
      if (iPointer == 0) {
         return;
      }

      size_t* memory = static_cast<size_t*>(iPointer);
      memory--;
      sCurrentUsage -= *memory;
      free(memory);
   }

}


size_t currentMemoryUsage() {
   return sCurrentUsage;
}

//-------------------------------------------------------------------------------------------------

void * operator new(size_t iSize)
{
   return checkedMalloc(iSize);
}

//-------------------------------------------------------------------------------------------------

void operator delete(void * iPointer)
{
   checkedFree(iPointer);
}

//-------------------------------------------------------------------------------------------------

void * operator new[](size_t iSize)
{
   return checkedMalloc(iSize);
}

//-------------------------------------------------------------------------------------------------

void operator delete[](void * iPointer)
{
   checkedFree(iPointer);
}

//-------------------------------------------------------------------------------------------------
