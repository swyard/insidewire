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

    // todo: while true ask for input try send

    // how do you send to server
}