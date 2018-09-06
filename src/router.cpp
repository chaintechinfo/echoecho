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
        // TODO
        // return connection_ptr( new Connection(_acceptor->get_io_service(), this) );
        return nullptr;
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
