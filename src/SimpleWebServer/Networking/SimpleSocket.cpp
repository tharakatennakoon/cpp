#include "SimpleSocket.h"

SWS::SimpleSocket::SimpleSocket(){}

SWS::SimpleSocket::SimpleSocket(int domain, int service, int protocol):
    domain(domain),
    service(service),
    protocol(protocol)
{
    
}

SWS::SimpleSocket::~SimpleSocket(){}

