//
// Created by shniu on 18-9-3.
//

#ifndef ECHOECHO_ROUTER_H
#define ECHOECHO_ROUTER_H

#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include "network/message.h"
#include "network/connection.h"

namespace echoecho {

    class Connection;
    class Protocol;

    using boost::asio::ip::tcp;

    // responsible for managing connections
    class Router {
    public:
        // Constructor opens the acceptor and starts waiting for
        // the first incoming connection.
        Router(boost::shared_ptr<tcp::acceptor> accp, Protocol *p, boost::function<string()> uuidf);

        // create a connection
        connection_ptr new_connection();

        // connect out to a remote server
        void connect_to_remote(tcp::endpoint &endpoint);

    private:
        void register_connection(connection_ptr conn);

        // all connections
        vector< connection_ptr > _connections;

        // acceptor
        boost::shared_ptr<tcp::acceptor> _acceptor;

    };

}

#endif //ECHOECHO_ROUTER_H
