//*************************************************************************************************
//
//  BITTAILOR.CH - ArduinoCore
//
//-------------------------------------------------------------------------------------------------
//
//  Bt::Com::TcpServer
//  
//*************************************************************************************************

#ifndef INC__Bt_Com_TcpServer__hpp
#define INC__Bt_Com_TcpServer__hpp

#include "I_RequestServer.hpp"
#include "EthernetServer.h"
#include "EthernetClient.h"
#include "StaticArrayPackageBuffer.hpp"
#include "BinaryInputPackage.hpp"
#include "BinaryOutputPackage.hpp"

namespace Bt {
namespace Com {



class TcpServer 
{
   public:

      enum { TCP_SERVER_BUFFER_LENGHT = 32};
      enum { TCP_SERVER_CHECK_BYTE    = 0xAF};


      TcpServer(EthernetServer& iServerSocket, I_RequestServer& iHandler);
      ~TcpServer();
   
      virtual void workcycle();

   private:
   	  // Constructor to prohibit copy construction.
      TcpServer(const TcpServer&);

      // Operator= to prohibit copy assignment
      TcpServer& operator=(const TcpServer&);

      void waitForClient();
      void waitForRequest();
      void readSize();
      void readData();

      size_t calculateReadSize(size_t iAvailable);
      bool checkConnection();

      typedef void (TcpServer::*StateFunction)();

      EthernetServer* mServerSocket;
      EthernetClient mSocket;
      StateFunction mStateFunction;
      I_RequestServer* mHandler;

      size_t mSize;

      StaticArrayPackageBuffer<TCP_SERVER_BUFFER_LENGHT> mInputBuffer;
      BinaryInputPackage mInput;
      StaticArrayPackageBuffer<TCP_SERVER_BUFFER_LENGHT> mOutputBuffer;
      BinaryOutputPackage mOutput;


};


} // namespace Com
} // namespace Bt

#endif // INC__Bt_Com_TcpServer__hpp
