#include "ServerInfoPacket.h"

void ServerInfoPacket::SetIP(string value) {
    ip = value;
    datachanged = true;
}

string ServerInfoPacket::GetIP() {
    return ip;
}

void ServerInfoPacket::SetPort(short value) {
    port = value;
    datachanged = true;
}

short ServerInfoPacket::GetPort() {
    return port;
}

void ServerInfoPacket::SetPlayers(short value) {
    players = value;
    datachanged = true;
}

void ServerInfoPacket::SetMaxPlayers(short value) {
    maxplayers = value;
    datachanged = true;
}

void ServerInfoPacket::SetUsePassword(bool value) {
    usepassword = value;
    datachanged = true;
}

void ServerInfoPacket::SetHostname(string value) {
    hostname = value;
    datachanged = true;
}

void ServerInfoPacket::SetMode(string value) {
    mode = value;
    datachanged = true;

}

void ServerInfoPacket::SetLanguage(string value) {
    language = value;
    datachanged = true;
}

byte* ServerInfoPacket::GetPayloadBytes() {
    if (datachanged) {
        ComputePayload();
        datachanged = false;
    }
    return payloadbytes;
}

int ServerInfoPacket::GetPayloadByteCount() {
    if (datachanged) {
        ComputePayload();
        datachanged = false;
    }
    return payloadbytecount;
}

void ServerInfoPacket::ComputePayload() {
    stringstream ss;
    ss << "SAMP";

    stringstream ss_ip(ip);
    int ipB1, ipB2, ipB3, ipB4;
    char tmpchar;
    ss_ip >> ipB1 >> tmpchar >> ipB2 >> tmpchar >> ipB3 >> tmpchar >> ipB4;

    ss << (unsigned char)ipB1 << (unsigned char)ipB2 << (unsigned char)ipB3 << (unsigned char)ipB4;

    unsigned char portB2 = (port) & 0xFF;
    unsigned char portB1 = (port >> 8) & 0xFF;

    ss << portB2 << portB1;
    ss << (unsigned char)105; // ?? dont know what is this (maybe opcode requested)
    ss << (unsigned char)(usepassword?1:0);

    unsigned char playersB2 = (players) & 0xFF;
    unsigned char playersB1 = (players >> 8) & 0xFF;

    ss << playersB2 << playersB1;

    unsigned char maxplayersB2 = (maxplayers) & 0xFF;
    unsigned char maxplayersB1 = (maxplayers >> 8) & 0xFF;

    ss << maxplayersB2 << maxplayersB1;

    int length = hostname.length();
    unsigned char lengthB1 = (length >> 24) & 0xFF;
    unsigned char lengthB2 = (length >> 16) & 0xFF;
    unsigned char lengthB3 = (length >> 8) & 0xFF;
    unsigned char lengthB4 = length & 0xFF;

    ss << lengthB4 << lengthB3 << lengthB2 << lengthB1;
    ss << hostname;

    length = mode.length();
    lengthB1 = (length >> 24) & 0xFF;
    lengthB2 = (length >> 16) & 0xFF;
    lengthB3 = (length >> 8) & 0xFF;
    lengthB4 = length & 0xFF;

    ss << lengthB4 << lengthB3 << lengthB2 << lengthB1;
    ss << mode;

    length = language.length();
    lengthB1 = (length >> 24) & 0xFF;
    lengthB2 = (length >> 16) & 0xFF;
    lengthB3 = (length >> 8) & 0xFF;
    lengthB4 = length & 0xFF;

    ss << lengthB4 << lengthB3 << lengthB2 << lengthB1;
    ss << language;

    string stringresult = ss.str();

    if (payloadbytes != NULL) delete payloadbytes;

    payloadbytes = new byte[stringresult.size()];

    for (unsigned int i = 0; i < stringresult.size(); i++) payloadbytes[i] = stringresult.at(i);

    payloadbytecount = stringresult.size();

}
