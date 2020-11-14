#include <Socket.h>

int Socket_Open(int* sockfd)
{
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(8001);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        if (bind(*sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) return 0;
    }
    if (listen(*sockfd, 1) < 0) return 0;
    return 1;
}
