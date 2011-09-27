//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Main of ArduinoCore test suite
//  
//*************************************************************************************************

#include <gtest/gtest.h>

#include <stdlib.h>

#include "MemoryUsage.hpp"



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

