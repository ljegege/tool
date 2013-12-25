#include "rsocket.h"

CRSocket::CRSocket()
{
    sockFd = -1;
    isConnect = false;
    isBind = false;
    //srcPort = -1;
    //destPort = -1;
}

CRSocket::~CRSocket()
{
    ::close(sockFd);
}
int CRSocket::sendto(char* psendData, int len, string strDestAddr, int destPort, int flag)
{
    if(sockFd < 0){
        return -1;
    }

    int sendCnt;
    // 判断是否已经connect
    if(isConnect){
        sendCnt = ::sendto(sockFd, psendData, len, 0, (struct sockaddr *)&destAddr, sizeof(destAddr));
    }
    else{
        struct sockaddr_in tmpDestAddr;
        tmpDestAddr.sin_family = AF_INET;
        tmpDestAddr.sin_port = htons(destPort);
        tmpDestAddr.sin_addr.s_addr = inet_addr(strDestAddr.c_str());
        sendCnt = ::sendto(sockFd, psendData, len, 0, (struct sockaddr *)&tmpDestAddr, sizeof(destAddr));
    }
    return sendCnt;
}

int CRSocket::recvfrom(char* precvData, int len, string *pstrDestAddr, int *pdestPort, int flag)
{
    if(sockFd < 0){
        return -1;
    }
    int recvCnt;
    socklen_t addrLen = sizeof(destAddr);
    if(pdestPort == NULL || pstrDestAddr == NULL){
        recvCnt = ::recvfrom(sockFd, precvData, len, 0, NULL, NULL);
    }
    else{
        struct sockaddr_in tmpDestAddr;
        recvCnt = ::recvfrom(sockFd, precvData, len, 0, (struct sockaddr *)&tmpDestAddr, &addrLen);
        *pstrDestAddr = inet_ntoa(tmpDestAddr.sin_addr);
        *pdestPort = ntohs(tmpDestAddr.sin_port);
    }
    return recvCnt;
}
bool CRSocket::create(int type)
{
    switch(type){
        case SOCK_DGRAM:{
            sockFd = socket(AF_INET, SOCK_DGRAM, 0);
            if(sockFd < 0){
                return false;
            }else{
                return true;
            }
        }
        default:{
            sockFd = -1;
            return false;
        }
    }
}

bool CRSocket::bind(char* pchSrcAddr, int srcPort)
{
    if(sockFd < 0){
        return -1;
    }
    // 如果socket未进行绑定则进行绑定
    if(!isBind){

        destAddr.sin_family = AF_INET;

        if(srcPort > 0){
            destAddr.sin_port = htons(srcPort);
        }else{
            // 未解决如何随机分配端口
            destAddr.sin_port = htons(startPort);
        }
        // 没有指定IP地址则绑定本机的所有地址，否则绑定制定的IP地址
        if(!pchSrcAddr){
            destAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        }else{
            destAddr.sin_addr.s_addr = inet_addr(pchSrcAddr);
        }

    }else{ // 重复绑定则返回false
        return false;
    }

    if(::bind(sockFd, (struct sockaddr *)&destAddr, sizeof(destAddr)) < 0){
        isBind = true;
        cout << errno << endl;
        perror("bind");
        return false;
    }else{
        return true;
    }
}

bool CRSocket::close()
{
    ::close(sockFd);
    sockFd = -1;
    return false;
}
