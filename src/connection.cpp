//
// Created by shniu on 18-9-3.
//

#include "network/connection.h"

namespace echoecho {
    Connection::Connection(boost::asio::io_service &io_service, Router *r) : _socket(io_service) {

    }

    tcp::socket& Connection::socket() {
        return _socket;
    }
}
