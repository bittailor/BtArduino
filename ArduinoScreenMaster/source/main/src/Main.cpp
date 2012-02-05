//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoScreenMaster
//
//-------------------------------------------------------------------------------------------------
//
//  Main
//  
//*************************************************************************************************

#include <Arduino.h>
#include <Bt/Ui/Colorduino.hpp>
#include <Bt/Ui/RgbScreenProxy.hpp>
#include <Bt/Ui/RgbScreenServer.hpp>
#include <Bt/Ui/CompoundRgbScreen.hpp>
#include <Bt/Com/TwoWireClient.hpp>
#include <Bt/Com/TcpServer.hpp>
#include <Bt/Com/Twi.hpp>
#include "EthernetServer.h"
#include "EthernetClient.h"
#include "Ethernet.h"
#include "Bt/Workcycle/MainWorkcycle.hpp"
#include "Bt/Workcycle/PeriodicWorkcycle.hpp"
#include "Bt/Io/DigitalOutput.hpp"
#include "Bt/Util/Time.hpp"


#define MASK 0xaa

// From linker script
extern int __heap_start, *__brkval;

// !!! This doesn't work together with malloc et.al. (whose use is
// !!! discouraged on AVR, anyway). alloca, however, is no problem
// !!! because it allocates on stack.

//  Get minimum of free memory (in bytes) up to now.
unsigned short
get_mem_unused (void)
{
   unsigned short unused = 0;


   unsigned char *p = ((unsigned char *)(__brkval == 0 ? (int) &__heap_start : (int) __brkval));

   do
   {
      if (*p++ != MASK)
         break;

      unused++;
   } while (p <= (unsigned char*) RAMEND);

   return unused;
}

// !!! Never call this function, it is part of .init-Code
void __attribute__ ((naked, used, section(".init3"))) init_mem (void);
void init_mem (void)
{
   //  Use inline assembler so it works even with optimization turned off
   __asm volatile (
      "ldi r30, lo8 (__heap_start)"  "\n\t"
      "ldi r31, hi8 (__heap_start)"  "\n\t"
      "ldi r24, %0"                  "\n\t"
      "ldi r25, hi8 (%1)"            "\n"
      "0:"                           "\n\t"
      "st  Z+,  r24"                 "\n\t"
      "cpi r30, lo8 (%1)"            "\n\t"
      "cpc r31, r25"                 "\n\t"
      "brlo 0b"
         :
         : "i" (MASK), "i" (RAMEND+1)
   );
}

static const unsigned long STARTUP_DELAY = 3000 ; // 3s

int freeRam () {

  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

Bt::Io::DigitalOutput mInterrupt(3);

void interruptCheck()
{
   mInterrupt.toggle();
}


class HeartBeat : public Bt::Workcycle::I_Runnable {
   public:
      HeartBeat(): mOutput(9) {
      }

      virtual void workcycle() {
         mOutput.toggle();
      }

   private:
      Bt::Io::DigitalOutput mOutput;

};

void configureDHCP() {
   byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

   while (Ethernet.begin(mac) == 0) {
      delay(1000);
   }

}

int main() {

   init();


   pinMode(2, INPUT);           // set pin to input
   digitalWrite(2, HIGH);       // turn on pullup resistors
   attachInterrupt(0, interruptCheck, FALLING);

   delay(STARTUP_DELAY);


   //Bt::Ui::Color black     (  0,  0,  0);
   Bt::Ui::Color red       (255,  0,  0);
   Bt::Ui::Color green     (  0,255,  0);
   //Bt::Ui::Color blue      (  0,  0,255);
   Bt::Ui::Color yellow    (255,255,  0);
   //Bt::Ui::Color white     (255,255,255);

   /*
   Bt::Com::Twi twi;
   Bt::Com::TwoWireClient<Bt::Com::Twi> server1(twi,1);
   Bt::Com::TwoWireClient<Bt::Com::Twi> server2(twi,2);

   Bt::Ui::RgbScreenProxy proxy1(server1);
   Bt::Ui::RgbScreenProxy proxy2(server2);
   Bt::Util::StaticMatrix<Bt::Ui::I_RgbScreen*,1,2> screens;
   screens(0,0) = &proxy1;
   screens(0,1) = &proxy2;

   Bt::Ui::CompoundRgbScreen screen(screens);
   screen.fill(red);
   screen.repaint();

   Bt::Ui::RgbScreenServer server(screen);
   */

   configureDHCP();

   //screen.fill(yellow);
   //screen.repaint();

   EthernetServer ethernetServer(2000);
   ethernetServer.begin();

   Bt::Com::TcpServer<EthernetServer,EthernetClient> tcpServer(ethernetServer);

   //screen.fill(green);
   //screen.repaint();

   Bt::Workcycle::MainWorkcycle workcycle;
   workcycle.add(tcpServer);

   Bt::Util::Time time;

   Bt::Workcycle::PeriodicWorkcycle periodic(1000uL*1000uL, time);
   workcycle.add(periodic);

   HeartBeat heartBeat;
   periodic.add(heartBeat);

   workcycle.run();

   return 0;
}
