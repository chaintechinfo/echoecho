//
// Created by niushaohan on 2018/8/22.
//

#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <cassert>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/thread/thread.hpp>

#include "src/server.hpp"
#include "src/client.hpp"
#include "network/router.h"

void show_usage() {

}

// simple server
void simple_echo_server(int argc, char** argv) {
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
}

// uuid gen function
std::string lame_uuid_gen() {
    boost::uuids::random_generator gen;
    boost::uuids::uuid uuid = gen();
    // #include <boost/lexical_cast.h>
    // boost::lexical_cast<std::string>(uuid);
    return boost::uuids::to_string(uuid);
}

void iorun( boost::asio::io_service * ios ) {
    ios->run();
    std::cout << "io ended" << std::endl;
}

int main(int argc, char** argv) {

    // simple_echo_server();

    // arg count
    auto port = static_cast<short>(atoi(argv[1]));
    std::cout << "Listening on port " << port << std::endl;

    boost::asio::io_service ios;

    boost::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor(
            new boost::asio::ip::tcp::acceptor(
                    ios,
                    boost::asio::ip::tcp::endpoint(
                            boost::asio::ip::tcp::v4(),
                            static_cast<unsigned short>(port)
                    )
            )
    );

    echoecho::Router router(acceptor, nullptr, boost::bind(&lame_uuid_gen));

    boost::thread t(boost::bind(&iorun, &ios));

    return 0;
}
