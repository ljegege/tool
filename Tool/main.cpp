#include <iostream>
#include <string.h>
#include "../rsocket.h"
using namespace std;

int main()
{
    CRSocket svrSocket;
    string destAddr;
    int port;
    svrSocket.create(SOCK_DGRAM);
    svrSocket.bind("125.216.227.108", 22200);
    char buf[100] = "0101010001";
    char rcvbuf[100];
    bzero(rcvbuf, 100);
    int bb = 0;
    for(int i = 0; i < 10000; i++){
        cout << "send len:" << svrSocket.sendto(buf, strlen(buf), "125.216.227.23", 22200, 0) << endl;
        if(svrSocket.recvfrom(rcvbuf, 100, &destAddr, &port, 0) > 0){
            cout << rcvbuf << endl;
            ++bb;
        }
    }
    cout << bb << endl;
    return 0;
}
