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

    printf("\n");
    char buf[BUF_SIZE + 1];
    // read, connectionless
    for (;;) {
        // client info
        int client_sockfd;
        char client_host[NI_MAXHOST],
            client_service[NI_MAXSERV];  // client host/service info bufs
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
                        client_host, NI_MAXHOST, client_service, NI_MAXSERV,
                        NI_NUMERICSERV) != 0) {
            char* client_host_sin_addr = inet_ntoa(client_sockaddr_in.sin_addr);
            snprintf(client_host, strlen(client_host_sin_addr), "%s",
                     client_host_sin_addr);
            snprintf(client_service, strlen(client_service), "%" PRIu16,
                     ntohs(client_sockaddr_in.sin_port));
        }
        printf(info, client_host, client_service, nread, buf);

        // send ack to client
        char read_ack[12];
        sprintf(read_ack, "%d", nread);
        size_t read_ack_len = strlen(read_ack);
        if (sendto(server_sock_fd, read_ack, read_ack_len, 0,
                   (struct sockaddr*)&client_sockaddr_in,
                   client_addr_len) != read_ack_len)
            perror("> ack");
        else
            printf("%s:%s >>> ack\n\n", client_host, client_service);
    }
}
