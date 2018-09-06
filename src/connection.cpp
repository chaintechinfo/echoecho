//
// Created by shniu on 18-9-3.
//

#include "network/connection.h"

namespace echoecho {

    connection::connection(uint16_t port)
            : _io_service{},
              _socket(_io_service),
              _acceptor(_io_service, tcp::endpoint(tcp::v4(), port)) {
    }

    connection::connection(boost::asio::io_service &io_service, uint16_t port)
            : _io_service(io_service),
              _socket(_io_service),
              _acceptor(_io_service, tcp::endpoint(tcp::v4(), port)) {

    }

    tcp::socket& connection::socket() {
        return _socket;
    }
}
