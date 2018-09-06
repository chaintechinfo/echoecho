//
// Created by shniu on 18-9-5.
//

#ifndef ECHOECHO_PROTOCOL_H
#define ECHOECHO_PROTOCOL_H

#include "network/router.h"

namespace echoecho {

    class Protocol {
    public:
        Protocol();

        virtual ~Protocol(){}

        virtual void set_router(Router * t) {

        }

    private:
        Router* m_router;
    };

} // echoecho

#endif //ECHOECHO_PROTOCOL_H
