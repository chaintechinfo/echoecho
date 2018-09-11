//
// Created by shniu on 18-9-11.
//

#include "network/protocol.h"

namespace echoecho {

    protocol::protocol() {
        cout << "New protocol ..." << endl;
    }

    bool protocol::new_incoming_connection(connection_ptr conn) {
        cout << "protocol::new_incoming_connection " << conn->str() << endl;
        return true;
    }

    void protocol::new_outgoing_connection(connection_ptr conn) {
        cout << "protocol::new_outgoing_connection " << conn->str() << endl;
    }

    void protocol::message_received(message_ptr msgp, connection_ptr conn) {
        cout << "protocol::message_received " << conn->str() << endl
             << msgp->str() << endl;
    }

}
