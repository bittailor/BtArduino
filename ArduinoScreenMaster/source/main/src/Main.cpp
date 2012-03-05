//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoScreenMaster
//
//-------------------------------------------------------------------------------------------------
//
//  Main
//  
//*************************************************************************************************


#include <Bt/Util/Time.hpp>
#include <Bt/Workcycle/MainWorkcycle.hpp>
#include <Bt/Workcycle/PeriodicWorkcycle.hpp>
#include <Bt/Com/TwoWireClient.hpp>
#include <Bt/Com/Twi.hpp>
#include <Bt/Com/TcpServer.hpp>
#include "Bt/Io/Heartbeat.hpp"
#include <Bt/Ui/Colorduino.hpp>
#include <Bt/Ui/RgbScreenProxy.hpp>
#include <Bt/Ui/RgbScreenServer.hpp>
#include <Bt/Ui/CompoundRgbScreen.hpp>
#include <Ethernet.h>
#include <EthernetServer.h>
#include <EthernetClient.h>

#include <Arduino.h>

//-------------------------------------------------------------------------------------------------

// 3s for the I2C slaves to start
#define STARTUP_DELAY 3000UL

#define HEARTBEAT_LED_PIN 9
#define HEARTBEAT_PERIOD 500000UL

static const Bt::Ui::Color RED       (255,  0,  0);
static const Bt::Ui::Color YELLOW    (255,255,  0);
static const Bt::Ui::Color GREEN     (  0,255,  0);

//-------------------------------------------------------------------------------------------------

void configureDHCP();

//-------------------------------------------------------------------------------------------------

int main() {

   init();

   Serial.begin(9600);

   delay(STARTUP_DELAY);

   // I2C slaves
   Bt::Com::Twi twi;
   Bt::Com::TwoWireClient<Bt::Com::Twi> server1(twi,1);
   Bt::Com::TwoWireClient<Bt::Com::Twi> server2(twi,2);
   Bt::Com::TwoWireClient<Bt::Com::Twi> server3(twi,3);
   Bt::Com::TwoWireClient<Bt::Com::Twi> server4(twi,4);

   // I2C led matrix proxies
   Bt::Ui::RgbScreenProxy proxy1(server1);
   Bt::Ui::RgbScreenProxy proxy2(server2);
   Bt::Ui::RgbScreenProxy proxy3(server3);
   Bt::Ui::RgbScreenProxy proxy4(server4);

   // Combine led matrixes to compund screen
   Bt::Util::StaticMatrix<Bt::Ui::I_RgbScreen*,2,2> screens;
   screens(0,0) = &proxy1;
   screens(0,1) = &proxy2;
   screens(1,0) = &proxy3;
   screens(1,1) = &proxy4;
   Bt::Ui::CompoundRgbScreen screen(screens);
   screen.fill(RED);
   screen.repaint();

   // TCP screen server
   Bt::Ui::RgbScreenServer server(screen);
   configureDHCP();
   screen.fill(YELLOW);
   screen.repaint();
   EthernetServer ethernetServer(2000);
   ethernetServer.begin();
   Bt::Com::TcpServer<EthernetServer,EthernetClient> tcpServer(ethernetServer,server);

   // Workcycle
   Bt::Workcycle::MainWorkcycle workcycle;
   workcycle.add(tcpServer);

   // Heartbeat LED
   Bt::Util::Time time;
   Bt::Workcycle::PeriodicWorkcycle periodic(HEARTBEAT_PERIOD, time);
   workcycle.add(periodic);
   Bt::Io::Heartbeat heartbeat(HEARTBEAT_LED_PIN);
   periodic.add(heartbeat);

   // Workcycle (for ever)
   screen.fill(GREEN);
   screen.repaint();
   workcycle.run();

   return 0;
}

//-------------------------------------------------------------------------------------------------

void configureDHCP() {
   byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
   while (Ethernet.begin(mac) == 0) {
      delay(1000);
   }
}

//-------------------------------------------------------------------------------------------------
