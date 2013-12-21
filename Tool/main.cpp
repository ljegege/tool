#include <iostream>
#include <string.h>
#include "../rsocket.h"
using namespace std;

int main()
{
    CRSocket svrSocket;
    svrSocket.create(SOCK_DGRAM);
    svrSocket.bind("125.216.227.108", 10086);
    char buf[100];
    bzero(buf, 100);
    svrSocket.recvfrom
    return 0;
}
