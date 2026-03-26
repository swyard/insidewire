#include <err.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "constants.h"

int main() {
    // create ip stream socket w/ tcp proto
    int server_sock_fd;
    if ((server_sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
        err(EXIT_FAILURE, "socket");
    printf("> socket\n");

    // bind
    struct in_addr server_in_addr;
    memset(&server_in_addr, 0, sizeof server_in_addr);
    inet_pton(AF_INET, LOCALHOST, &server_in_addr);

    struct sockaddr_in server_sockaddr_in;
    memset(&server_sockaddr_in, 0, sizeof server_sockaddr_in);
    server_sockaddr_in.sin_family = AF_INET;
    server_sockaddr_in.sin_port = htons(TCP_PORT);
    server_sockaddr_in.sin_addr = server_in_addr;

    if (bind(server_sock_fd, (struct sockaddr*)&server_sockaddr_in,
             sizeof(server_sockaddr_in)) == -1)
        err(EXIT_FAILURE, "bind");
    printf("> bind %d\n", TCP_PORT);

    // listen

    // accept or connect

    // communicate

    // todo: multiple clients
}