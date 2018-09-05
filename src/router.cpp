//
// Created by shniu on 18-9-5.
//

#include <utility>

#include "network/router.h"

namespace echoecho {
    Router::Router(boost::shared_ptr<tcp::acceptor> accp, Protocol *p, boost::function<string()> uuidf)
            : _acceptor( accp ) {

    }

    connection_ptr Router::new_connection() {
        boost::asio::io_context io_context = _acceptor->get_executor().context();
        boost::asio::io_service io_service = io_context;
        return connection_ptr( new Connection(io_service, this) );
    }

    void Router::connect_to_remote(tcp::endpoint &endpoint) {
        cout << "router::connect_to_remote("
             << endpoint.address().to_string() << ":"
             << endpoint.port() << ")"
             << endl;
        connection_ptr new_conn = new_connection();

        new_conn->socket();
    }
}
