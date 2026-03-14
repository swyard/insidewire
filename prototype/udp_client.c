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
    // setup socket
    int client_sock_fd;
    if ((client_sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        err(EXIT_FAILURE, "socket");
    printf("socket\n");

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

    // send
    char message[BUF_SIZE]; // bug-y needs terminatation?
    strcpy(message, "Hello Server!");
    if (sendto(client_sock_fd, message, sizeof message, 0,
               (struct sockaddr*)&server_sockaddr_in,
               sizeof server_sockaddr_in) != sizeof message) {
        perror("send");
    }

    // todo: while true ask for input try send
}