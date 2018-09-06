//
// Created by shniu on 18-9-3.
//

#ifndef ECHOECHO_CONNECTION_H
#define ECHOECHO_CONNECTION_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

// #include "network/message.h"

namespace echoecho {

    using boost::asio::io_service;
    using boost::asio::ip::tcp;

    class connection :
            boost::enable_shared_from_this<connection> {
    public:
        typedef boost::shared_ptr<connection> connection_ptr;

        static connection_ptr create(boost::asio::io_service& io_service, uint16_t port) {
            return connection_ptr(new connection(io_service, port));
        }

        ~connection();

        // Get the connection underlying socket
        tcp::socket& socket();

    private:
        connection( uint16_t port );
        connection( boost::asio::io_service &io_service, uint16_t port );

        // io service
        boost::asio::io_service _io_service;

        // underlying socket
        tcp::socket _socket;

        // acceptor
        tcp::acceptor _acceptor;
    };

}

#endif //ECHOECHO_CONNECTION_H
