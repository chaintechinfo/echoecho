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

int echosock::i_listen(int fd, int n) {
    if (listen(fd, n) == -1) {
        perror("* listen error");
        exit(1);
    }
    return 0;
}

int echosock::i_recv(int fd, void *buf, int maxsize) {
    int recvbytes;
    if ((recvbytes = static_cast<int>(recv(fd, buf, static_cast<size_t>(maxsize), 0))) == -1) {
        perror("recv error");
        return -1;
    }
    return recvbytes;
}
