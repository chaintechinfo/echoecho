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

#include "network/peer.h"
#include "utils/cxxopts.h"

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

// temp
void temp(int argc, char** argv) {
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
}


int main(int argc, char** argv) {
    // simple_echo_server();

    // Parse utils command to parse self port and p2p-peer-address
    // e.g. > ./echoecho -p 5555 --p2p-peer-address 192.168.1.96:5555
    cxxopts::Options options(argv[0], " - command line options");
    options.positional_help("[optional args]").show_positional_help();
    bool apple = false;
    options.add_options()
            ("f,file", "File name", cxxopts::value<std::string>(), "");
    options.add_options()
            ("help", "Print help", cxxopts::value<std::string>(), "Help");
    options.parse_positional({"input", "output", "positional"});
    auto result = options.parse(argc, argv);
    // the network must have many peers
    //peer p;
    //p.start();

    return 0;
}

/**
 * 迭代一目标： 构建一个p2p网络, 可以广播消息, 每个连接的节点都能收到消息并显示出来
 *   1. 启动一个节点服务，手动指定连接的节点地址
 *   2. 当有一个节点连接到自己后注册到自己的已连接节点列表中
 *   3. 任何一个节点都可以接受输入，将消息广播出去, 提供一个命令行输入
 *
 * 迭代二目标： 在已有的p2p网络基础之上, 做节点消息保存
 *   1. 节点可以将收到的消息按照接受顺序保存在一个文件中
 *
 * 迭代三目标： 添加节点发现功能
 * 迭代四目标： 给每个节点添加rpc(or http)调用服务和客户端cli命令行调用工具
 * 迭代五目标： 升级消息格式，将消息封装成一个block，消息存储成为blockchain
 * 迭代六目标： 为客户端程序添加公私钥对创建功能，并可以生成地址
 */
