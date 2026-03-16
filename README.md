# insidewire
networks programming: datagram and stream sockets


## docs

### sockets
- socket(7) https://man7.org/linux/man-pages/man7/socket.7.html
- socket(2) https://man7.org/linux/man-pages/man2/socket.2.html
- address_families(7) https://man7.org/linux/man-pages/man7/address_families.7.html
- bind(2) https://man7.org/linux/man-pages/man2/bind.2.html
- getsockopt(2) https://linux.die.net/man/2/getsockopt
- setsockopt(2) https://man.freebsd.org/cgi/man.cgi?query=setsockopt&sektion=2

### protocols
- protocols(5) https://man7.org/linux/man-pages/man5/protocols.5.html
- ip(7) https://man7.org/linux/man-pages/man7/ip.7.html

### connection
- getaddrinfo(3) https://man7.org/linux/man-pages/man3/getaddrinfo.3.html
- getnameinfo(3) https://man7.org/linux/man-pages/man3/getnameinfo.3.html
- inet_pton(3) https://man7.org/linux/man-pages/man3/inet_pton.3.html

### messaging
- recvfrom(2) https://man7.org/linux/man-pages/man2/recvfrom.2.html

## resources
- unix domain sockets vs internet sockets https://lists.freebsd.org/pipermail/freebsd-performance/2005-February/001143.html
- udp usage guidelines https://www.rfc-editor.org/rfc/rfc8085.html

## todo research

Address Family / Network Systems (Internet4, Internet6, Unix, Packet, Bluetooth)
\
—— Socket type (how to send data)
  \
   —— Protocol (if multiple for a data type)

- packet sniffer
- interfaces, why so many, how to read em, what are they, how do they fit in, ip link
- packet https://man7.org/linux/man-pages/man7/packet.7.html
- mtu https://www.cloudflare.com/learning/network-layer/what-is-mtu/, and more
- udp usage guidelines https://www.rfc-editor.org/rfc/rfc8085.html
- udp-lite https://www.rfc-editor.org/rfc/rfc3828
- ip fragmentation https://en.wikipedia.org/wiki/IP_fragmentation
- anicast, multicast, unicast, broadcast etc
- req int hosts comm layers https://www.rfc-editor.org/rfc/rfc1122
- congestion control protocols https://www.rfc-editor.org/rfc/rfc2914