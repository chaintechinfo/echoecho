//
// Created by niushaohan on 2018/8/22.
//
#pragma once

#ifndef ECHOECHO_SERVER_HPP
#define ECHOECHO_SERVER_HPP

#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <zconf.h>
#include "i_sock.hpp"
#include "utils.hpp"

namespace echoserver {

    using namespace echosock;

#define SERVER_PORT 6666

    // start server
    int main();
}

#endif //ECHOECHO_SERVER_HPP
