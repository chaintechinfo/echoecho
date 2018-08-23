//
// Created by niushaohan on 2018/8/22.
//

#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <cassert>

#include "src/server.hpp"
#include "src/client.hpp"

void show_usage() {

}

int main(int argc, char** argv) {

    // getopt
    int s_flag = 0;
    char *server_addr = nullptr;
    char* server_port = nullptr;
    int act;
    while ((act = getopt(argc, argv, "scd:p:")) != -1) {
        switch (act) {
            case 's':
                s_flag = 1;
                break;
            case 'c':
                s_flag = 0;
                break;
            case 'd':
                server_addr = optarg;
                break;
            case 'p':
                server_port = optarg;
                break;
            default:
                perror("argument error");
                exit(1);
        }
    }

    if (s_flag == 1) {
        echoserver::main();
    } else {
        assert(server_addr != nullptr);
        assert(server_port != nullptr);

        echoclient::main(server_addr, server_port);
    }


    return 0;
}
