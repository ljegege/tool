#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <string>
using namespace std;
class CRSocket
{
private:
    int sockFd;
    bool isConnect;
    bool isBind;
    struct sockaddr_in srcAddr;
    struct sockaddr_in destAddr;
    //int srcPort, destPort;

public:
    CRSocket();
    ~CRSocket();
    int sendto(char* psendData, int len, string strDestAddr, int destPort, int flag = 0);
    int recvfrom(char* precvData, int len, string *pstrDestAddr, int *pdestPort, int flag = 0);
    bool close();
    bool create(int type);
    bool bind(char* pchSrcAddr, int srcPort);
};