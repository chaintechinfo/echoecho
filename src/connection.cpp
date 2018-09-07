//
// Created by shniu on 18-9-7.
//

#include "network/connection.h"

namespace echoecho {
    connection::connection(io_service &ios) : _socket(ios) {}

    tcp::socket& connection::socket() {
        return _socket;
    }

    void connection::async_read() {

    }
}
