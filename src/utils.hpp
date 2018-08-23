//
// Created by niushaohan on 2018/8/23.
//
#pragma once

#ifndef ECHOECHO_UTILS_HPP
#define ECHOECHO_UTILS_HPP

#include <cstdio>
#include <cstring>
#include <string>

namespace echoutils {

#define STAR "*"
#define LENGTH 20

    std::string star_str();

    int message(char* msg);

    void message(int len);
}

#endif //ECHOECHO_UTILS_HPP
