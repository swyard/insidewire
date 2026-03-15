#include <arpa/inet.h>
#include <err.h>
#include <inttypes.h>
#include <netdb.h>
#include <netinet/ip.h> /* includes netinet/in.h */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

#include "constants.h"

int main() {
    // setup socket
    int client_sock_fd;
    if ((client_sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        err(EXIT_FAILURE, "socket");
    printf("> socket\n");

    // timeout 1s0ms (for server ack)
    struct timeval timeval = {1, 0};
    if (setsockopt(client_sock_fd, SOL_SOCKET, SO_RCVTIMEO, &timeval,
                   sizeof timeval) == -1)
        err(EXIT_FAILURE, "timeout");

    // server info
    struct in_addr server_in_addr;
    memset(&server_in_addr, 0, sizeof server_in_addr);
    if (inet_pton(AF_INET, LOCALHOST, &server_in_addr) != 1)
        err(EXIT_FAILURE, "in_addr");

    struct sockaddr_in server_sockaddr_in;
    memset(&server_sockaddr_in, 0, sizeof server_sockaddr_in);
    server_sockaddr_in.sin_family = AF_INET;
    server_sockaddr_in.sin_port = htons(UDP_PORT);
    server_sockaddr_in.sin_addr = server_in_addr;
    socklen_t server_addr_len = sizeof(server_sockaddr_in);

    char server_host[NI_MAXHOST], server_serv[NI_MAXSERV];
    if (getnameinfo((struct sockaddr*)&server_sockaddr_in,
                    sizeof server_sockaddr_in, server_host, NI_MAXHOST,
                    server_serv, NI_MAXSERV, AI_NUMERICSERV) != 0) {
        snprintf(server_host, sizeof LOCALHOST, "%s", LOCALHOST);
        snprintf(server_serv, sizeof server_serv, "%" PRIu16, UDP_PORT);
    }

    printf("\n");
    // send, connectionless
    char input[BUF_SIZE + 1];
    char recv_buf[RECV_BUF_SIZE + 1];
    for (;;) {
        printf("%s:%s >>> ", server_host, server_serv);
        fflush(stdout);

        if (fgets(input, sizeof input, stdin) == NULL) break;
        input[strcspn(input, "\n")] = '\0';
        size_t input_len = strlen(input);

        int sent;
        if ((sent = sendto(client_sock_fd, input, input_len, 0,
                           (struct sockaddr*)&server_sockaddr_in,
                           sizeof server_sockaddr_in)) != input_len)
            perror("> send");
        else
            printf("> sent %d bytes\n", sent);

        // ack from server
        int recv;
        if ((recv = recvfrom(client_sock_fd, recv_buf, RECV_BUF_SIZE, 0,
                             (struct sockaddr*)&server_sockaddr_in,
                             &server_addr_len)) < 0)
            perror("< receive");
        else {
            recv_buf[recv] = '\0';

            if (atoi(recv_buf) != sent)
                perror("< ack");
            else
                printf("< ack\n\n", server_host, server_serv);
        }

        printf("\n");
    }
}