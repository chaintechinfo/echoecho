//
// Created by shniu on 18-9-6.
//

#include "network/node.h"

namespace echoecho {

    node::node(network &p2p)
            : _p2p(p2p) {
    }

    node::~node() {}

    void node::start_listening() {
        cout << "Start the node server" << endl;
        _p2p.awake();
    }

}

