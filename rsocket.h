#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
using namespace std;

const int startPort = 2000;
const int maxUdpPort = 65535;
class CRSocket
{
private:
    int sockFd;
    int sockType;
    bool isConnect;
    bool isBind;
    int sockType;
    struct sockaddr_in srcAddr;
    struct sockaddr_in destAddr;
    //int srcPort, destPort;
protected:
    inline bool verifyAddrPort(string addr, int port);
public:
    CRSocket();
    ~CRSocket();
    int create(int type);
    int connect(string strDestAddr, int destPort);
    int sendto(char* psendData, int len, string strDestAddr = "", int destPort = -1, int flag = 0);
    int recvfrom(char* precvData, int len, string *pstrDestAddr = NULL, int *pdestPort = NULL, int flag = 0);
    bool close();

    int bind(string strSrcAddr = "", int srcPort = -1);
};
