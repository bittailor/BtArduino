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
#include "Bt/Io/DigitalOutput.hpp"
#include <Bt/Ui/Colorduino.hpp>
#include <Bt/Ui/RgbScreenProxy.hpp>
#include <Bt/Ui/RgbScreenServer.hpp>
#include <Bt/Ui/CompoundRgbScreen.hpp>
#include <Ethernet.h>
#include <EthernetServer.h>
#include <EthernetClient.h>

// 3s for the I2C slaves to start
#define STARTUP_DELAY 3000UL

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

   delay(STARTUP_DELAY);

   Bt::Ui::Color red       (255,  0,  0);
   Bt::Ui::Color green     (  0,255,  0);
   Bt::Ui::Color yellow    (255,255,  0);

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

   configureDHCP();

   screen.fill(yellow);
   screen.repaint();

   EthernetServer ethernetServer(2000);
   ethernetServer.begin();

   EthernetServer dummy1(3001);
   EthernetServer dummy2(3002);
   EthernetServer dummy3(3003);

   Bt::Com::TcpServer<EthernetServer,EthernetClient> tcpServer(ethernetServer,server);

   screen.fill(green);
   screen.repaint();

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
