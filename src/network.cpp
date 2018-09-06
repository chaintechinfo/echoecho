//
// Created by shniu on 18-9-6.
//

#include "network/network.h"

namespace echoecho {

    network::network(uint16_t port)
            : _port(port), _running(false) {
        // acceptor

    }

    void network::awake() {
        if (!_running) {
            boost::asio::io_service io_service;
            _self_conn_ptr = connection::create(io_service, _port);
            _running = true;
        }
    }

    void network::broadcast(const string &message) {
        cout << "Succeed broadcast " << message << endl;
    }

}
