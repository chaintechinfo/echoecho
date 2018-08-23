//
// Created by niushaohan on 2018/8/23.
//

#include "client.hpp"

namespace echoclient {

    void main(char* addr, char* port) {
        echoutils::message(const_cast<char *>(" ECHO CLIENT "));
        printf("* Connect to addr: %s, port: %s\n", addr, port);

        // Get socket
        int client_fd = echosock::i_socket(AF_INET, SOCK_STREAM, 0);

        // connect
        struct sockaddr_in server_addr;
        bzero((char *) &server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(atoi(port));
        server_addr.sin_addr.s_addr = inet_addr(addr);
        if (connect(client_fd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr)) == -1) {
            printf("connect error");
            exit(1);
        }

        printf("* Connect server succeed.\n");

        const char* msg  = "Hello";
        // Send
        if (send(client_fd, msg, strlen(msg), 0) == -1) {
            printf("send error");
            exit(0);
        }

        // Recv
        int recvbytes;
        char buf[1000];
        if ((recvbytes = static_cast<int>(recv(client_fd, buf, 1000, 0))) == -1) {
            printf("recv error");
            exit(1);
        }

        buf[recvbytes] = '\0';
        printf("Received: %s\n", buf);
    }

}
