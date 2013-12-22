#include <iostream>
#include <string.h>
#include "../rsocket.h"
using namespace std;

int main()
{
    CRSocket svrSocket;
    svrSocket.create(SOCK_DGRAM);
    svrSocket.bind("", 10086);
    char buf[100];
    bzero(buf, 100);
    int rtCnt = svrSocket.recvfrom(buf, 100);
    cout << rtCnt << endl;
    return 0;
}
