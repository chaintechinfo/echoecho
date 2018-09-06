//
// Created by niushaohan on 2018/8/22.
//

#include "server.hpp"

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
    i_listen(listen_fd, 20);

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
            // son process
            char buf[1000] = {0};
            int recvbytes = i_recv(client_fd, buf, 1000);
            buf[recvbytes] = '\0';
            printf("* \tmessage is: %s\n", buf);

            char * msg = buf;
            if (send(client_fd, msg, static_cast<size_t>(recvbytes), 0) == -1) {
                printf("* send error");
            }
            close(client_fd);
            exit(0);
        }
    }

    echoutils::message(len);
    return 0;
}

// simple server
/*void simple_echo_server(int argc, char** argv) {
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
}*/
