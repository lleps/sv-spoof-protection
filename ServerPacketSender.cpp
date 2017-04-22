#include "ServerPacketSender.h"
#include <crafter.h>

using namespace Crafter;

ServerPacketSender::ServerPacketSender(string iface) {
    this->iface = iface;
}

void ServerPacketSender::Send(string srcIP, short srcPort, string dstIP, short dstPort, ServerInfoPacket* packet) {
    IP ip_header;
    ip_header.SetSourceIP(srcIP);
    ip_header.SetDestinationIP(dstIP);

    UDP udp_header;
    udp_header.SetSrcPort(srcPort);
    udp_header.SetDstPort(dstPort);

    RawLayer payload;
    payload.SetPayload(packet->GetPayloadBytes(), packet->GetPayloadByteCount());

    Packet packetToSend(ip_header / udp_header / payload);
    packetToSend.Send(iface);
}
