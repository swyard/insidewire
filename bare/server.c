#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netinet/ip.h> /* includes netinet/in.h */
#include <sys/socket.h>
#include <sys/types.h>

#define LOCALHOST "127.0.0.1"
#define PORT 42389

int main() {
    // create ip datagram socket w/ udp proto
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        err(EXIT_FAILURE, "socket");
    printf("socket\n");

    // bind info
    struct in_addr inaddr;
    inet_pton(AF_INET, LOCALHOST, &inaddr);

    struct sockaddr_in sockaddrin;
    memset(&sockaddrin, 0, sizeof sockaddrin);
    sockaddrin.sin_family = AF_INET;
    sockaddrin.sin_port = htons(PORT);
    sockaddrin.sin_addr = inaddr;
    memset(sockaddrin.sin_zero, 0, sizeof sockaddrin.sin_zero);
    
    // bind
    if (bind(sockfd, (struct sockaddr *) &sockaddrin, sizeof(sockaddrin)) == -1)
        err(EXIT_FAILURE, "bind");
    printf("bind\n");
}
