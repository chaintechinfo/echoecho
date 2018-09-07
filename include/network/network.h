//
// Created by shniu on 18-9-6.
//

#ifndef ECHOECHO_NETWORK_H
#define ECHOECHO_NETWORK_H

#include <iostream>
#include <string>


namespace echoecho {
    using namespace std;

    class network {
    public:
        network(uint16_t port);

        void broadcast(const string &);
        void received();

        // Startup the network if non running
        void awake();

        uint16_t port() {
            return _port;
        }
    private:
        // the port that self node listen on this network
        uint16_t _port;

        // self connection
        // connection::connection_ptr _self_conn_ptr;

        // running or not
        bool _running;

        // manage connections

    };

}

#endif //ECHOECHO_NETWORK_H
