//
// Created by shniu on 18-9-3.
//

#ifndef ECHOECHO_CONNECTION_H
#define ECHOECHO_CONNECTION_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include "network/message.h"

namespace echoecho {

    using boost::asio::io_service;
    using boost::asio::ip::tcp;

    class Connection :
            boost::enable_shared_from_this<Connection> {
    public:

        Connection( boost::asio::io_service& io_service, Router * r );

        ~Connection();

        // Get the connection underlying socket
        tcp::socket& socket();

    private:
        // Connection(io_service &io);

        // underlying socket
        tcp::socket _socket;
    };

}

#endif //ECHOECHO_CONNECTION_H
