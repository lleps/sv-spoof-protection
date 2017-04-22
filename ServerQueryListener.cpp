#include "ServerQueryListener.h"
#include <crafter.h>

using namespace Crafter;

void DebugPayload(string payload);

void UDPQueryHandler(Packet* packet, void* listener_ptr) {
    IP* ip_layer = packet->GetLayer<IP>();
    UDP* udp_layer = packet->GetLayer<UDP>();
    RawLayer* payload_layer = packet->GetLayer<RawLayer>();

    if (ip_layer && udp_layer && payload_layer) {
        string str = payload_layer->GetStringPayload();
        if ((str.at(0) == 'S' && str.at(1) == 'A' && str.at(2) == 'M' && str.at(3) == 'P')
        && (str.size() == 11 || str.size() == 15)) {
            ServerQueryListener* sql = (ServerQueryListener*) listener_ptr;
            sql->listener_function(ip_layer->GetSourceIP(), udp_layer->GetSrcPort(),
                          ip_layer->GetDestinationIP(), udp_layer->GetDstPort(),
                          str.at(10));
        }
    }
    //cout << ip_layer->GetSourceIP() << ":" << udp_layer->GetSrcPort() << " > ";
    //cout << ip_layer->GetDestinationIP() << ":" << udp_layer->GetDstPort() << endl;
    //cout << "size: " << payload_layer->GetStringPayload().size() << " - " << payload_layer->GetStringPayload() << endl;
    //DebugPayload(payload_layer->GetStringPayload());
}

ServerQueryListener::ServerQueryListener(string iface, void (*listener_function)(string, short, string, short, char)) {
    this->listener_function = listener_function;
    Sniffer* sniffer = new Sniffer("udp", iface, UDPQueryHandler);
    sniffer->Spawn(-1, this);
}
