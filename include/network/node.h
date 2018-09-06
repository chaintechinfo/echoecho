//
// Created by shniu on 18-9-6.
//

#ifndef ECHOECHO_PEER_H
#define ECHOECHO_PEER_H

#include <iostream>
#include <vector>
#include <string>

namespace echoecho {
    using namespace std;

    class node {
    public:
        node();
        ~node();

        // start a peer server
        void start_listening();
    private:
        // connection to others todo
        vector<string> _connections;
    };
}



#endif //ECHOECHO_PEER_H
