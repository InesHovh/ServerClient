#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <sys/select.h>

class Server
{
private:
    char buf[4096];
    int socket_fd;
    int new_socket;
    struct sockaddr_in sockaddr;
    struct sockaddr_in new_sockaddr;
public:
    Server(int port);
    void Listen();
    void Accept();
    void ClientHandling();
    ~Server();

};


#endif