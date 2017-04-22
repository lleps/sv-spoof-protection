#ifndef _serverpacketsender_h
#define _serverpacketsender_h

#include <iostream>
#include "ServerInfoPacket.h"

using namespace std;

class ServerPacketSender {

public:
    ServerPacketSender(string iface);

    void Send(string srcIP, short srcPort, string dstIP, short dstPort, ServerInfoPacket* packet);

private:
    string iface;
};

#endif // _serverpacketsender_h
