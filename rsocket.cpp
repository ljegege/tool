#include "rsocket.h"

CRSocket::CRSocket()
{
    sockFd = -1;
    sockType = -1;
    isConnect = false;
    isBind = false;
}

CRSocket::~CRSocket()
{
    ::close(sockFd);
}

inline bool CRSocket::verifyAddrPort(string addr, int port)
{
    if(port == -1 || addr == "") {
        return false;
    } else {
        return true;
    }
}
int CRSocket::sendto(char* psendData, int len, string strDestAddr, int destPort, int flag)
{
    if(sockFd < 0 || sockType != SOCK_DGRAM) {
        return -1;
    }

    if(!verifyAddrPort(strDestAddr, destPort)) {
        // 判断是否已经connect
        if(isConnect) {
            return ::sendto(sockFd, psendData, len, 0, (struct sockaddr *)&destAddr, sizeof(destAddr));
        } else {
            return -1;
        }

    } else {
        struct sockaddr_in tmpDestAddr;
        tmpDestAddr.sin_family = AF_INET;
        tmpDestAddr.sin_port = htons(destPort);
        tmpDestAddr.sin_addr.s_addr = inet_addr(strDestAddr.c_str());
        return ::sendto(sockFd, psendData, len, 0, (struct sockaddr *)&tmpDestAddr, sizeof(destAddr));
    }
}

int CRSocket::recvfrom(char* precvData, int len, string *pstrDestAddr, int *pdestPort, int flag)
{
    if(sockFd < 0 || sockType != SOCK_DGRAM) {
        return -1;
    }
    int recvCnt;
    socklen_t addrLen = sizeof(destAddr);
    if(pdestPort == NULL || pstrDestAddr == NULL) {
        recvCnt = ::recvfrom(sockFd, precvData, len, 0, NULL, NULL);
    } else {
        struct sockaddr_in tmpDestAddr;
        recvCnt = ::recvfrom(sockFd, precvData, len, 0, (struct sockaddr *)&tmpDestAddr, &addrLen);
        *pstrDestAddr = inet_ntoa(tmpDestAddr.sin_addr);
        *pdestPort = ntohs(tmpDestAddr.sin_port);
    }
    return recvCnt;
}
int CRSocket::create(int type)
{
    switch(type) {
    case SOCK_DGRAM: {
        sockFd = socket(AF_INET, SOCK_DGRAM, 0);
        if(sockFd < 0) {
            return -1;
        } else {
            sockType = type;
            return 0;
        }
    }
    default: {
        sockFd = -1;
        return -1;
    }
    }
}

int CRSocket::connect(string strDestAddr, int destPort)
{
    if(sockFd < 0 || isConnect) {
        return -1;
    }
    if(sockType == SOCK_DGRAM) {
        if(verifyAddrPort(strDestAddr, destPort)) {
            destAddr.sin_family = AF_INET;
            destAddr.sin_port = htons(destPort);
            destAddr.sin_addr.s_addr = inet_addr(strDestAddr.c_str());
            isConnect = true;
            return true;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

int CRSocket::bind(string strSrcAddr, int srcPort)
{
    if(sockFd < 0) {
        return -1;
    }
    // 如果socket未进行绑定则进行绑定
    if(isBind) {
        return false;
    }
    srcAddr.sin_family = AF_INET;
    // 没有指定IP地址则绑定本机的所有地址，否则绑定制定的IP地址
    if(strSrcAddr == "") {
        srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
        srcAddr.sin_addr.s_addr = inet_addr(strSrcAddr.c_str());
    }

    if(srcPort > 0) {
        srcAddr.sin_port = htons(srcPort);
        if(::bind(sockFd, (struct sockaddr *)&srcAddr, sizeof(srcAddr)) < 0) {
            perror("bind");
            return false;
        } else {
            isBind = true;
            return true;
        }
    } else {
        // 未指定端口时则随机分配端口
        for(int port = startPort; port <= maxUdpPort; ++port) {
            srcAddr.sin_port = htons(port);
            if(::bind(sockFd, (struct sockaddr *)&srcAddr, sizeof(srcAddr)) == 0) {
                continue;
            } else {
                isBind = true;
                return true;
            }
        }
        return false;
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
