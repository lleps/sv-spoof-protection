#ifndef _serverquerylistener_h_
#define _serverquerylistener_h_

#include <iostream>

using namespace std;

class ServerQueryListener {
public:

    ServerQueryListener(string iface, void (*listener_function)(string, short, string, short, char));

void (*listener_function)(string, short, string, short, char);
};

#endif // _serverquerylistener_h_
