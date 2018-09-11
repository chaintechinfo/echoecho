//
// Created by shniu on 18-9-11.
//

#ifndef ECHOECHO_PROTOCOL_H
#define ECHOECHO_PROTOCOL_H

#include "network/node.h"
#include "network/connection.h"

namespace echoecho {

    class protocol {
    public:
        protocol();
        virtual ~protocol(){}

        virtual void set_node(node* n) {
            node = n;
        }

        // called when a client connects to us
        virtual bool new_incoming_connection( connection_ptr conn );

        // called when we opened a socket to a remote server
        virtual void new_outgoing_connection( connection_ptr conn );

        // called on a disconnection, for whatever reason
        virtual void connection_terminated( connection_ptr conn ){}

        // we received a msg from this connection
        virtual void message_received( message_ptr msgp, connection_ptr conn );

    protected:
        node * node;
    };
}

#endif //ECHOECHO_PROTOCOL_H
