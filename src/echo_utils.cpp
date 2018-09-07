//
// Created by niushaohan on 2018/8/23.
//

#include "utils/echo_utils.h"

std::string echoutils::star_str() {
    std::string s_;
    for (int i = 0; i < LENGTH; i++) {
        s_.append(STAR);
    }
    return s_;
}

int echoutils::message(char *msg) {
    std::string result;
    result.append(star_str());
    result.append(msg);
    result.append(star_str());
    printf("%s\n", result.c_str());
    return static_cast<int>(result.length());
}

void echoutils::message(int len) {
    std::string s;
    for (int i = 0; i < len; i++) {
        s.append(STAR);
    }
    printf("%s\n", s.c_str());
}
