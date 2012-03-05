//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Ui::Colorduino
//  
//*************************************************************************************************

#include "Bt/Ui/Colorduino.hpp"

#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#define RST_BIT 0x04
#define LAT_BIT 0x02
#define SLB_BIT 0x01
#define SCL_BIT 0x40
#define SDA_BIT 0x80

#define RST PORTC
#define LAT PORTC
#define SLB PORTC
#define SDA PORTD
#define SCL PORTD

#define OPEN_LINE_7()      {PORTB=0x01;}
#define OPEN_LINE_6()      {PORTB=0x02;}
#define OPEN_LINE_5()      {PORTB=0x04;}
#define OPEN_LINE_4()      {PORTB=0x08;}
#define OPEN_LINE_3()      {PORTB=0x10;}
#define OPEN_LINE_2()      {PORTB=0x20;}
#define OPEN_LINE_1()      {PORTD=0x08;}
#define OPEN_LINE_0()      {PORTD=0x10;}
#define CLOSE_ALL_LINES()  {PORTD=0x00;PORTB=0x00;}

#define LED_RST_SET RST|=RST_BIT
#define LED_RST_CLR RST&=~RST_BIT
#define LED_SDA_SET SDA|=SDA_BIT
#define LED_SDA_CLR SDA&=~SDA_BIT
#define LED_SCL_SET SCL|=SCL_BIT
#define LED_SCL_CLR SCL&=~SCL_BIT
#define LED_LAT_SET LAT|=LAT_BIT
#define LED_LAT_CLR LAT&=~LAT_BIT
#define LED_SELBNK_SET SLB|=SLB_BIT
#define LED_SELBNK_CLR SLB&=~SLB_BIT

namespace Bt {
namespace Ui {

inline void timer2Callback() {
   Bt::Util::Singleton<Bt::Ui::Colorduino>::instance()->workcycle();
}

void ledDelay(unsigned char i)
{
  unsigned int y;
  y = i * 10;
  while(y--);
}



} // namespace Ui
} // namespace Bt

ISR(TIMER2_OVF_vect)          //Timer2 Interrupt
{
   TCNT2 = 0x64;      //flash a led matrix frequency is 100.3Hz,period is 9.97ms
   Bt::Ui::timer2Callback();
}

namespace Bt {
namespace Ui {

//-------------------------------------------------------------------------------------------------

Colorduino::Colorduino(int iWhiteBalanceAddress)
: mSingletonInstance(*this)
, mScreens()
, mWrite(0)
, mRead(1)
, mCurrentLine(0)
, mWhiteBalanceAddress(reinterpret_cast<uint8_t*>(iWhiteBalanceAddress)) {
   initIo();
   initLed();
   initTimerIsr();
   initWhiteBalance();
}

//-------------------------------------------------------------------------------------------------

Colorduino::~Colorduino() {

}

//-------------------------------------------------------------------------------------------------

void Colorduino::initIo() {
   DDRD = 0xff; // set all pins direction of PortD
   DDRC = 0xff; // set all pins direction of PortC
   DDRB = 0xff; // set all pins direction of PortB

   PORTD = 0x00; // set all pins output is low of PortD
   PORTC = 0x00; // set all pins output is low of PortC
   PORTB = 0x00; // set all pins output is low of PortB
}

//-------------------------------------------------------------------------------------------------

void Colorduino::initLed() {
   LED_RST_SET;
   ledDelay(1);
   LED_RST_CLR;
   ledDelay(1);
   LED_RST_SET;
   ledDelay(1);
}

//-------------------------------------------------------------------------------------------------

void Colorduino::initTimerIsr() {
   TCCR2A |= (1 << WGM21) | (1 << WGM20);
   TCCR2B |= ((1<<CS22)|(1<<CS20));          // by clk/64
   TCCR2B &= ~((1<<CS21));                   // by clk/64
   TCCR2A &= ~((1<<WGM21) | (1<<WGM20));     // Use normal mode
   ASSR |= (1<<AS2);                         // Use internal clock - external clock not used in Arduino
   TIMSK2 |= (1<<TOIE2) | (0<<OCIE2B);       //Timer2 Overflow Interrupt Enable
   TCNT2 = 0xff;
   sei();
}

//-------------------------------------------------------------------------------------------------

void Colorduino::initWhiteBalance() {
   enum {N_COLORS = 3};

   uint8_t colors[N_COLORS] = {};

   for (int i = 0; i < N_COLORS; ++i) {
      colors[i] = eeprom_read_byte(mWhiteBalanceAddress+i);
      if (colors[i] > MAX_WHITE_BALANCE) {
         colors[i] = MAX_WHITE_BALANCE;
      }
   }
   setWhiteBalance(Color(colors[0],colors[1],colors[2]),0);

}

//-------------------------------------------------------------------------------------------------

uint8_t Colorduino::numberOfSegments() {
   return 1;
}
//-------------------------------------------------------------------------------------------------

Color Colorduino::whiteBalance(uint8_t iSegment) {
   return mWhiteBalance;
}

//-------------------------------------------------------------------------------------------------

void Colorduino::setWhiteBalance(Color iColor, uint8_t iSegment) {
   mWhiteBalance = iColor;
   LED_LAT_CLR;
   LED_SELBNK_CLR;
   for (unsigned int x = 0; x < WIDTH; ++x) {
      shiftOut(iColor,6);
   }
   LED_SELBNK_SET;
}

//-------------------------------------------------------------------------------------------------

void Colorduino::persistWhiteBalance(uint8_t iSegment) {
   eeprom_write_byte(mWhiteBalanceAddress,mWhiteBalance.red());
   eeprom_write_byte(mWhiteBalanceAddress+1,mWhiteBalance.green());
   eeprom_write_byte(mWhiteBalanceAddress+2,mWhiteBalance.blue());
}

//-------------------------------------------------------------------------------------------------

size_t Colorduino::width() {
   return WIDTH;
}

//-------------------------------------------------------------------------------------------------

size_t Colorduino::height() {
   return HEIGHT;
}

//-------------------------------------------------------------------------------------------------

void Colorduino::setPixel(uint8_t iX, uint8_t iY, Color iColor) {
   mScreens[mWrite](iY,iX) = iColor;
}

//-------------------------------------------------------------------------------------------------

void Colorduino::fill(Color iColor) {
   for(unsigned int x = 0 ; x < WIDTH ; ++x) {
      for(unsigned int y = 0 ; y < HEIGHT ; ++y) {
         mScreens[mWrite](y,x) = iColor;
      }
   }
}

//-------------------------------------------------------------------------------------------------

void Colorduino::repaint() {
   ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
      uint8_t swap = mWrite;
      mWrite = mRead;
      mRead = swap;
   }
   mScreens[mWrite] = mScreens[mRead];
}

//-------------------------------------------------------------------------------------------------

inline void Colorduino::shiftOut(uint8_t value, uint8_t numberOfBits) {
   if (numberOfBits < BITS_PER_BYTE) {
      value <<= (8 - numberOfBits);
   }

   for(unsigned int bit = 0 ; bit < numberOfBits ; ++bit) {
      if(value & 0x80)
         LED_SDA_SET;
      else
         LED_SDA_CLR;
      value <<= 1;
      LED_SCL_CLR;
      LED_SCL_SET;
   }
}

//-------------------------------------------------------------------------------------------------

inline void Colorduino::shiftOut(const Color& iColor, uint8_t numberOfBits) {
   shiftOut(iColor.blue(),numberOfBits);
   shiftOut(iColor.green(),numberOfBits);
   shiftOut(iColor.red(),numberOfBits);
}

//-------------------------------------------------------------------------------------------------

inline void Colorduino::writeCurrentLine() {
   LED_SELBNK_SET;
   LED_LAT_CLR;

   for(unsigned int x = 0 ; x < WIDTH ; ++x)
   {
      shiftOut(mScreens[mRead](mCurrentLine,x));
   }
   LED_LAT_SET;
   LED_LAT_CLR;
}

//-------------------------------------------------------------------------------------------------

inline void Colorduino::openCurrentLine() {
   switch (mCurrentLine)
   {
      case 0 : OPEN_LINE_0()     ; break;
      case 1 : OPEN_LINE_1()     ; break;
      case 2 : OPEN_LINE_2()     ; break;
      case 3 : OPEN_LINE_3()     ; break;
      case 4 : OPEN_LINE_4()     ; break;
      case 5 : OPEN_LINE_5()     ; break;
      case 6 : OPEN_LINE_6()     ; break;
      case 7 : OPEN_LINE_7()     ; break;
      default: CLOSE_ALL_LINES() ; break;
   }
}

//-------------------------------------------------------------------------------------------------

inline void Colorduino::incrementCurrentLine() {
   mCurrentLine = (mCurrentLine + 1) % 8;
}

//-------------------------------------------------------------------------------------------------

void Colorduino::workcycle() {
   CLOSE_ALL_LINES();
   writeCurrentLine();
   openCurrentLine();
   incrementCurrentLine();
}

//-------------------------------------------------------------------------------------------------
} // namespace Ui
} // namespace Bt
