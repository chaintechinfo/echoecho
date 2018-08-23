//
// Created by niushaohan on 2018/8/22.
//

#ifndef ECHOECHO_I_SOCK_HPP
#define ECHOECHO_I_SOCK_HPP

#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>

namespace echosock {

    // i_socket
    // Usage: i_socket(AF_INET, SOCK_STREAM, 0)
    int i_socket(int domain, int type, int protocol) {
        int fd;

        if ((fd = socket(domain, type, protocol)) == -1) {
            perror("Get socket error");
            exit(1);
        }
        return fd;
    }

    // i_bind
    int i_bind(int fd, const struct sockaddr * addr, int namelen) {
        if (bind(fd, addr, static_cast<socklen_t>(namelen)) == -1) {

        }

        return 0;
    }

}


#endif //ECHOECHO_I_SOCK_HPP
