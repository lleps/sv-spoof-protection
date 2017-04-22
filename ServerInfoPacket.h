#ifndef _serverinfopacket_h_
#define _serverinfopacket_h_

#include <iostream>
#include <fstream>
#include <string>
#include <crafter.h>

using namespace std;
using namespace Crafter;

class ServerInfoPacket {

public:

    void SetIP(string ip);
    string GetIP();

    void SetPort(short port);
    short GetPort();

    void SetPlayers(short players);
    void SetMaxPlayers(short maxplayers);

    void SetUsePassword(bool usepassword);

    void SetHostname(string hostname);
    void SetMode(string mode);
    void SetLanguage(string language);

    byte* GetPayloadBytes();
    int GetPayloadByteCount();

private:

    string ip = "0.0.0.0";
    short port = 7777;

    short players;
    short maxplayers;

    bool usepassword = false;

    string hostname;
    string mode;
    string language;

    byte* payloadbytes = NULL;
    int payloadbytecount;

    bool datachanged = false;

    void ComputePayload();
};

#endif // _serverinfopacket_h_
