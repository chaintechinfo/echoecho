//
// Created by shniu on 18-9-3.
//

#include "network/connection.h"

namespace echoecho {
    tcp_connection::connection(io_service &io) : _socket(io) {

    }
}
