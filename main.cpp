#include <iostream>
#include <vector>
#include <string>
#include <crafter.h>
#include <sys/time.h>
#include <unordered_map>
#include <mutex>

#include "FileUtils.h"
#include "ServerInfoPacket.h"
#include "ServerPacketSender.h"
#include "ServerQueryListener.h"

using namespace std;

const char* SV_DATA_FILE = "scriptfiles/server-info.txt";

class RequestData {
public:
   short port;
   time_t timestamp;

   RequestData(short porte, time_t timestampe) : port(porte), timestamp(timestampe) {}
};

unordered_map<string, RequestData*> requests;
const int REQUEST_EXPIRE_TIME = 60 * 3; // in secs

vector<ServerInfoPacket*> packets_to_send;

mutex mtx;

ServerInfoPacket* sv_packet = NULL;

void OnQueryReceived(string srcIP, short srcPort, string dstIP, short dstPort, char opcode) {
    if (sv_packet == NULL) {
        sv_packet = new ServerInfoPacket();

        sv_packet->SetIP(dstIP);
        sv_packet->SetPort(dstPort);
        // some default data
        sv_packet->SetHostname("Carga spoof_protection.amx!!");
        sv_packet->SetMode("Carga spoof_protection.amx!!");
        sv_packet->SetLanguage("Carga spoof_protection.amx!!");

        cout << "Server IP: " << dstIP << ":" << dstPort << endl;
        packets_to_send.push_back(sv_packet);
    }

    if (opcode == 'i') {
        mtx.lock();
        pair<string, RequestData*> entry(srcIP, new RequestData(srcPort, time(0)));
        requests.insert(entry);
        mtx.unlock();
    }
}

void SendDataToRequest(ServerPacketSender* sender, string ip, RequestData* request) {
    //cout << "sending data to " << ip << ":" << request->port << endl;
    for (auto iter : packets_to_send) {
        ServerInfoPacket* packet = iter;
        sender->Send(packet->GetIP(), packet->GetPort(), ip, request->port, packet);
    }
}

void UpdatePacketByFile() {
    if (sv_packet != NULL) {
        vector<string>* file_lines = loadFileLines(SV_DATA_FILE);
        if (file_lines) {
            vector<string> lines = *file_lines;
            short players = stoi(lines[0]);
            short maxplayers = stoi(lines[1]);
            string hostname = lines[2];
            string mode = lines[3];
            string language = lines[4];
            sv_packet->SetPlayers(players);
            sv_packet->SetMaxPlayers(maxplayers);
            sv_packet->SetHostname(hostname);
            sv_packet->SetMode(mode);
            sv_packet->SetLanguage(language);
            //cout << players << "|" << maxplayers << "|" << hostname << "|" << mode << "|" << language << endl;
        } else {
            cout << "[sv-spoof-protection] No se pudo leer informacion desde " << SV_DATA_FILE << endl;
        }
    }
}

int main() {
    string iface = "wlan0"; //eth0 eth1 etc..
    cout << "Iniciando en interfaz " << iface << ".." << endl;

    ServerQueryListener query_listener(iface, &OnQueryReceived);
    ServerPacketSender sender(iface);

    bool running = true;

    while (running) {
        UpdatePacketByFile();
        mtx.lock();
        unordered_map<string, RequestData*>::iterator itr = requests.begin();
        while (itr != requests.end()) {
            
            string ip = itr->first;
            RequestData* request = itr->second;

            unsigned int time_since_request = time(0) - request->timestamp;
            if (time_since_request > REQUEST_EXPIRE_TIME) {
                itr = requests.erase(itr);
                delete request;
                //cout << "request from " << ip << " expired" << endl;
            } else {
                SendDataToRequest(&sender, ip, request);
                itr++;
            }
        }
        mtx.unlock();

        sleep(1); // 1 means 1 second (not millisecond)
    }
    return 0;
}
