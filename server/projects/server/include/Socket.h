#ifndef METRO_SOCKET_H
#define METRO_SOCKET_H
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int Socket_Open(int* sockfd);

#endif
