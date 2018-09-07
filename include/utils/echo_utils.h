//
// Created by shniu on 18-9-7.
//

#ifndef ECHOECHO_ECHO_UTILS_H
#define ECHOECHO_ECHO_UTILS_H

#include <iostream>
#include <string>

namespace echoutils {

#define STAR "*"
#define LENGTH 20

    std::string star_str();

    int message(char* msg);

    void message(int len);
}

#endif //ECHOECHO_ECHO_UTILS_H
