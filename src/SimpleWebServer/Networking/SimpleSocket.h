#pragma once

#include <sys/socket.h>
#include <fmt/core.h>

class SimpleSocket
{
public:
    SimpleSocket(int domain, int service, int protocol);

    ~SimpleSocket();
    SimpleSocket(SimpleSocket &);
    SimpleSocket &operator=(const SimpleSocket &);

private:
    SimpleSocket();

private:
    int domain      = AF_INET;
    int service     = SOCK_STREAM;
    int protocol    = 0;
};