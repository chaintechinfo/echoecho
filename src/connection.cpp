//
// Created by shniu on 18-9-3.
//

#include "network/connection.h"

namespace echoecho {

    connection::connection(boost::asio::io_service &io_service, uint16_t port)
            : _socket(io_service),
              _acceptor(io_service, tcp::endpoint(tcp::v4(), port)) {

    }

    tcp::socket& connection::socket() {
        return _socket;
    }
}
