#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>

class Client
{
private:
    struct sockaddr_in server_addr;
    char buf[4096];
    int client_socket;
public:
    Client(int port);
    void Connect();
    void SendReceive();
    ~Client();
};

#endif