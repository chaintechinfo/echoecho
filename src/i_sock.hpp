//
// Created by niushaohan on 2018/8/22.
//
#pragma once

#ifndef ECHOECHO_I_SOCK_HPP
#define ECHOECHO_I_SOCK_HPP

#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>

namespace echosock {

    // i_socket
    // Usage: i_socket(AF_INET, SOCK_STREAM, 0)
    int i_socket(int domain, int type, int protocol);

    // i_bind
    int i_bind(int fd, const struct sockaddr * addr, int namelen);

    // i_listen
    int i_listen(int fd, int n);

    // i_recv
    int i_recv(int fd, void *buf, int maxsize);

}


#endif //ECHOECHO_I_SOCK_HPP
