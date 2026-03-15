#include <arpa/inet.h>
#include <err.h>
#include <inttypes.h>
#include <netdb.h>
#include <netinet/ip.h> /* includes netinet/in.h */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "constants.h"

int main() {
    // create ip datagram socket w/ udp proto
    int server_sock_fd;
    if ((server_sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        err(EXIT_FAILURE, "socket");
    printf("> socket\n");

    // bind info
    struct in_addr server_in_addr;
    memset(&server_in_addr, 0, sizeof server_in_addr);
    inet_pton(AF_INET, LOCALHOST, &server_in_addr);

    struct sockaddr_in server_sockaddr_in;
    memset(&server_sockaddr_in, 0, sizeof server_sockaddr_in);
    server_sockaddr_in.sin_family = AF_INET;
    server_sockaddr_in.sin_port = htons(UDP_PORT);
    server_sockaddr_in.sin_addr = server_in_addr;

    // bind
    if (bind(server_sock_fd, (struct sockaddr*)&server_sockaddr_in,
             sizeof(server_sockaddr_in)) == -1)
        err(EXIT_FAILURE, "bind");
    printf("> bind %d\n", UDP_PORT);

    char buf[BUF_SIZE + 1];
    // read, connectionless
    for (;;) {
        // client info
        int client_sockfd;
        char host[NI_MAXHOST],
            service[NI_MAXSERV];  // client host/service info bufs
        struct sockaddr_in client_sockaddr_in;
        socklen_t client_addr_len = sizeof(client_sockaddr_in);

        int nread =
            recvfrom(server_sock_fd, buf, BUF_SIZE, 0,
                     (struct sockaddr*)&client_sockaddr_in, &client_addr_len);
        if (nread == -1) {
            perror("< receive");
            continue;
        }

        buf[nread] = '\0';
        char* info = "%s:%s %d bytes <<< %s\n";

        // reverse dns lookup
        if (getnameinfo((struct sockaddr*)&client_sockaddr_in, client_addr_len,
                        host, NI_MAXHOST, service, NI_MAXSERV,
                        NI_NUMERICSERV) == 0) {
            printf(info, host, service, nread, buf);
        } else {
            char port[6];  // u16
            snprintf(port, sizeof port, "%" PRIu16,
                     ntohs(client_sockaddr_in.sin_port));
            printf(info, inet_ntoa(client_sockaddr_in.sin_addr), port, nread,
                   buf);
        }

        // todo: send ack to client
    }
}
