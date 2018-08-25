//
// Created by niushaohan on 2018/8/23.
//
#pragma once

#ifndef ECHOECHO_CLIENT_HPP
#define ECHOECHO_CLIENT_HPP

#include <cstdio>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include "utils.hpp"
#include "i_sock.hpp"

namespace echoclient {
    void send_recv(sockaddr_in &server_addr, char* msg);

    void main(char* addr, char* port);
}

#endif //ECHOECHO_CLIENT_HPP
