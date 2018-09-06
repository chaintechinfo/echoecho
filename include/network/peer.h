//
// Created by shniu on 18-9-6.
//

#ifndef ECHOECHO_PEER_H
#define ECHOECHO_PEER_H

#include <vector>
#include <string>

namespace echoecho {
    using namespace std;

    class peer {
    public:
        peer();
        ~peer();

        // start a peer server
        void start();
    private:
        // connection to others
        vector<string> _connections;
    };
}



#endif //ECHOECHO_PEER_H
