//
// Created by niushaohan on 2018/8/22.
//

#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <cassert>
#include <iostream>
#include <string>

#include "utils/cxxopts.h"
#include "network/node.h"


int main(int argc, char** argv) {

    // Parse utils command to parse self port and p2p-peer-address
    // e.g. > ./echoecho -p 5555 --p2p-peer-address 192.168.1.96:5555
    cxxopts::Options options(argv[0], "- command line options");

    options.positional_help("[optional args]")
            .show_positional_help();

    int s_port = 5555;
    typedef std::vector<std::string> str_vector;
    str_vector peer_vector;

    options.add_options()
            ("p,port", "Server port", cxxopts::value<int>(s_port), "int type");
    options.add_options()
            ("p2p-peer-address", "p2p address", cxxopts::value<str_vector>(peer_vector), "Other peer");
    options.add_options()
            ("help", "Print help");

    // options.parse_positional({"input", "output", "positional"});
    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        // std::cout << options.help({"", "Group"}) << std::endl;
        std::cout << options.help({""}) << std::endl;
        exit(0);
    }

    // std::cout << "Server listening on " << s_port << std::endl;

    if (result.count("p2p-peer-address")) {
        std::cout << peer_vector.size() << std::endl;
        std::cout << peer_vector[0] << std::endl;
        std::cout << peer_vector[1] << std::endl;
    }

    // the network must have many peers
    echoecho::network network(static_cast<uint16_t>(s_port));
    echoecho::node s_node(network);
    s_node.start_listening();

    // input
    std::string message;
    std::cout << "Enter message -> ";
    std::getline(std::cin, message);
    while (message != "/q") {
        // broadcast
        network.broadcast(message);
        std::cout << "Broadcast: " << message << std::endl;

        std::cout << "Enter message -> ";
        std::getline(std::cin, message);
    }

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
