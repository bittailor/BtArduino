//*************************************************************************************************
//
//  BITTAILOR.CH - NightLight
//
//-------------------------------------------------------------------------------------------------
//
//  Settings
//  
//*************************************************************************************************

#ifndef INC__Settings__hpp
#define INC__Settings__hpp

// 3s for the I2C slaves to start
#define STARTUP_DELAY 2500UL

#define NUMBER_OF_BUTTONS 4
#define CAPACITIVE_SENSOR_SEND_PIN 3
#define CAPACITIVE_SENSOR_NEXT_RECEIVE_PIN 4
#define CAPACITIVE_SENSOR_PREVIOUS_RECEIVE_PIN 7
#define CAPACITIVE_SENSOR_HIGH_THRESHOLD 1000
#define CAPACITIVE_SENSOR_LOW_THRESHOLD 500

#define IMAGE_DIM_FACTOR 32


#endif // INC__Settings__hpp
