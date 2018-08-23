//
// Created by niushaohan on 2018/8/22.
//

#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <zconf.h>
#include "server.hpp"
#include "i_sock.hpp"
#include "utils.hpp"

using namespace echosock;

int echoserver::main() {
    int len = echoutils::message(const_cast<char *>(" ECHO SERVER "));

    // var
    int listen_fd;

    // open socket
    listen_fd = i_socket(AF_INET, SOCK_STREAM, 0);

    // bind
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(SERVER_PORT);
    bzero(&(my_addr.sin_zero), 8);
    i_bind(listen_fd, reinterpret_cast<const sockaddr *>(&my_addr), sizeof(struct sockaddr));

    // listen
    if (listen(listen_fd, 20) == -1) {
        perror("* listen error");
        exit(1);
    }
    printf("* Echo server start succeed, listen port: %d\n", SERVER_PORT);

    int sin_size;
    int client_fd;
    struct sockaddr_in remote_addr;

    while (true) {
        sin_size = sizeof(struct sockaddr_in);
        if ((client_fd = accept(listen_fd, (sockaddr *) &remote_addr, (socklen_t *)&sin_size)) == -1) {
            perror("* accept error");
            continue;
        }

        printf("* Received a connection from %s:%d\n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port));

        int pid = fork();
        if (pid == 0) {
            close(client_fd);
            exit(0);
        }
    }

    echoutils::message(len);
    return 0;
}
