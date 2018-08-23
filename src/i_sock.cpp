//
// Created by niushaohan on 2018/8/23.
//

#include "i_sock.hpp"

int echosock::i_socket(int domain, int type, int protocol) {
    int fd;

    if ((fd = socket(domain, type, protocol)) == -1) {
        perror("Get socket error");
        exit(1);
    }
    return fd;
}

int echosock::i_bind(int fd, const struct sockaddr *addr, int namelen) {
    if (bind(fd, addr, static_cast<socklen_t>(namelen)) == -1) {
        perror("Bind error");
        exit(1);
    }

    return 0;
}
