//
// Created by shniu on 18-9-3.
//

#ifndef ECHOECHO_ROUTER_H
#define ECHOECHO_ROUTER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include "network/message.h"

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

    private:
        void register_connection(connection_ptr conn);

    };

}

#endif //ECHOECHO_ROUTER_H
