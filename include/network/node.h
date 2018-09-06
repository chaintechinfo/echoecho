//
// Created by shniu on 18-9-6.
//

#ifndef ECHOECHO_PEER_H
#define ECHOECHO_PEER_H

#include <iostream>
#include <vector>
#include <string>

#include "network/network.h"

namespace echoecho {
    using namespace std;

    class node {
    public:
        node(network &p2p);
        ~node();

        // Get p2p network
        network& p2p() {
            return _p2p;
        }

        // start a peer server
        void start_listening();
    private:
        // connection to others todo
        vector<string> _connections;

        // p2p network
        network _p2p;
    };
}



#endif //ECHOECHO_PEER_H
