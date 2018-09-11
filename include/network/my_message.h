//
// Created by shniu on 18-9-11.
//

#ifndef ECHOECHO_MY_MESSAGE_H
#define ECHOECHO_MY_MESSAGE_H

#include "network/message.h"

namespace echoecho {

#define PING 0
#define PONG 1
#define QUERY 2

    class PongMessage : public message {
    public:
        PongMessage(string uid) {
            message_header h;
            memcpy( &h.guid, uid.c_str(), 36 );
            h.type = PONG;
            h.ttl = 1;
            h.hops = 0;
            h.length = 0;
            _header = h;
            _payload = 0;
        }
    };

    class PingMessage : public message {
    public:
        PingMessage(string uid) {
            message_header h;
            memcpy(&h.guid, uid.c_str(), 36);
            h.type = PING;
            h.ttl = 1;
            h.hops = 0;
            h.length = 0;
            _header = h;
            _payload = 0;
        }
    };

}

#endif //ECHOECHO_MY_MESSAGE_H
