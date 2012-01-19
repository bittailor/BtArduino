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

static const unsigned long STARTUP_DELAY = 3000 ; // 3s


int main() {

   init();

   Serial.begin(9600);
   //Serial.begin(115200);

   Serial.println("Startup");

   delay(STARTUP_DELAY);

   Serial.println("Colors");

   Bt::Ui::Color black     (  0,  0,  0);
   Bt::Ui::Color red       (255,  0,  0);
   Bt::Ui::Color green     (  0,255,  0);
   Bt::Ui::Color blue      (  0,  0,255);
   Bt::Ui::Color yellow    (255,255,  0);
   Bt::Ui::Color white     (255,255,255);

   Serial.println("Twi");
   Bt::Com::Twi twi;
   Bt::Com::TwoWireClient<Bt::Com::Twi> server1(twi,1);
   Bt::Com::TwoWireClient<Bt::Com::Twi> server2(twi,2);

   Serial.println("Twi Screens");
   Bt::Ui::RgbScreenProxy proxy1(server1);
   Bt::Ui::RgbScreenProxy proxy2(server2);
   Bt::Util::StaticMatrix<Bt::Ui::I_RgbScreen*,1,2> screens;
   screens(0,0) = &proxy1;
   screens(0,1) = &proxy2;

   Serial.println("Compound");
   Bt::Ui::CompoundRgbScreen screen(screens);
   screen.fill(red);
   screen.repaint();

   Serial.println("RgbServer");
   Bt::Ui::RgbScreenServer server(screen);

   byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

   Serial.print("DHCP");
   while (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using DHCP ...");
      Serial.println(" ... wait for a retry ...");
      delay(1000);
      Serial.println(" ... retry");
   }

   Serial.print("My IP address: ");
   IPAddress ip = Ethernet.localIP();
   for (byte thisByte = 0; thisByte < 4; thisByte++) {
      // print the value of each byte of the IP address:
      Serial.print(ip[thisByte], DEC);
      Serial.print(".");
   }
   Serial.println();

   screen.fill(yellow);
   screen.repaint();

   Serial.println("EthernetServer");
   EthernetServer ethernetServer(2000);
   ethernetServer.begin();

   Bt::Com::TcpServer<EthernetServer,EthernetClient> tcpServer(ethernetServer,server);

   screen.fill(green);
   screen.repaint();

   Serial.println("workcycle");
   while(true) {
      tcpServer.workcycle();
   }

   return 0;
}
