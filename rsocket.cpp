#include "rsocket.h"

CRSocket::CRSocket()
{
    sockFd = -1;
<<<<<<< HEAD
    isConnect = false;
    isBind = false;
    //srcPort = -1;
    //destPort = -1;
=======
    sockType = -1;
    isConnect = false;
    isBind = false;
>>>>>>> 42bae5ac6135d09c90330e74b925e1af2e476625
}

CRSocket::~CRSocket()
{
    ::close(sockFd);
}

inline bool CRSocket::verifyAddrPort(string addr, int port)
{
    if(port == -1 || addr == ""){
        return false;
    }else{
        return true;
    }
}
int CRSocket::sendto(char* psendData, int len, string strDestAddr, int destPort, int flag)
{
    if(sockFd < 0 || sockType != SOCK_DGRAM){
        return -1;
    }

    if(!verifyAddrPort(strDestAddr, destPort)){
        // 判断是否已经connect
        if(isConnect){
            return ::sendto(sockFd, psendData, len, 0, (struct sockaddr *)&destAddr, sizeof(destAddr));
        }else{
            return -1;
        }

    }
    else{
        struct sockaddr_in tmpDestAddr;
        tmpDestAddr.sin_family = AF_INET;
        tmpDestAddr.sin_port = htons(destPort);
        tmpDestAddr.sin_addr.s_addr = inet_addr(strDestAddr.c_str());
        return ::sendto(sockFd, psendData, len, 0, (struct sockaddr *)&tmpDestAddr, sizeof(destAddr));
    }
}

int CRSocket::recvfrom(char* precvData, int len, string *pstrDestAddr, int *pdestPort, int flag)
{
    if(sockFd < 0 || sockType != SOCK_DGRAM){
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
int CRSocket::create(int type)
{
    switch(type){
        case SOCK_DGRAM:{
            sockFd = socket(AF_INET, SOCK_DGRAM, 0);
            if(sockFd < 0){
                return -1;
            }else{
                sockType = type;
                return 0;
            }
        }
        default:{
            sockFd = -1;
            return -1;
        }
    }
}

int CRSocket::connect(string strDestAddr, int destPort)
{
    if(sockFd < 0 || isConnect){
        return -1;
    }
    if(sockType == SOCK_DGRAM){
        if(verifyAddrPort(strDestAddr, destPort)){
            destAddr.sin_family = AF_INET;
            destAddr.sin_port = htons(destPort);
            destAddr.sin_addr.s_addr = inet_addr(strDestAddr.c_str());
            isConnect = true;
            return true;
        }else{
            return -1;
        }
    }else{
        return -1;
    }
}

int CRSocket::bind(string strSrcAddr, int srcPort)
{
    if(sockFd < 0){
        return -1;
    }
    // 如果socket未进行绑定则进行绑定
    if(!isBind){
<<<<<<< HEAD

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
=======
        srcAddr.sin_family = AF_INET;

        if(srcPort > 0){
            srcAddr.sin_port = htons(srcPort);
        }else{
            // 之后将其改成随机分配端口
            return -1;
        }
        // 没有指定IP地址则绑定本机的所有地址，否则绑定指定的IP地址
        if(strSrcAddr == ""){
            srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        }else{
            srcAddr.sin_addr.s_addr = inet_addr(strSrcAddr.c_str());
        }

    }else{ // 重复绑定则返回false
        return -1;
    }

    if(::bind(sockFd, (struct sockaddr *)&srcAddr, sizeof(srcAddr)) < 0){
        return -1;
    }else{
        isBind = true;
        return 0;
>>>>>>> 42bae5ac6135d09c90330e74b925e1af2e476625
    }
}

bool CRSocket::close()
{
    ::close(sockFd);
    sockFd = -1;
    sockType = -1;
    isConnect = false;
    isBind = false;
    return false;
}
