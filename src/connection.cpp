//
// Created by shniu on 18-9-3.
//

#include "network/connection.h"

namespace echoecho {
    Connection::Connection(io_service &io) : _socket(io) {
    }
}
