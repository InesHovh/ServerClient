// #include "Server.hpp"

// int main()
// {
//     char buf[4096];

//     int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
//     if (socket_fd == -1)
//     {
        // std::cout << "Failed to connect: " << errno <<std::endl;
//         exit(EXIT_FAILURE);
//     }

//     std::cout << "Connected" << std::endl;

//     struct sockaddr_in sockaddr;

//     sockaddr.sin_family = AF_INET;
//     sockaddr.sin_port = htons(9999);
//     sockaddr.sin_addr.s_addr = INADDR_ANY; // htonl("127.0.0.1") 

//     if(bind(socket_fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
//     {
        // std::cout << "Failed to bind. " << std::endl;
//         return 1;
//     }

//     if(listen(socket_fd, 10) == 0){
//         std::cout << "Listen..." << std::endl;
//     }else{
//         return 1;
//     }

//     struct sockaddr_in new_sockaddr;
//     socklen_t size = sizeof(new_sockaddr);

//     int new_socket = accept(socket_fd, (struct sockaddr*)&new_sockaddr, &size);

//     if (new_socket < 0)
//     {
//         std::cout << "Failed to accept with client." << std::endl;
//         return 1;    
//     }


//     std::cout << "Connected to the client." << std::endl;


//     while(1)
//     {
//         recv(new_socket, buf, sizeof(buf), 0);
//         std::cout << "Client: " << buf << std::endl;
//         std::cout << "Server: ";
//         memset(buf, 0, 4096);
//         std::cin.getline(buf , 4096);
//         send(new_socket, buf, strlen(buf), 0);
//         memset(buf, 0, 4096);

//     }

//     close(new_socket);
// }

#include "Server.hpp"

Server::Server(int port) {
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        std::cout << "Failed to connect: " << errno <<std::endl;
        exit(EXIT_FAILURE);
    }

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    sockaddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socket_fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
        std::cout << "Failed to bind. " << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Server::Listen() {
    if (listen(socket_fd, 10) == 0) {
        std::cout << "Listen..." << std::endl;
    } else {
        exit(EXIT_FAILURE);
    }
}

void Server::Accept() {
    socklen_t addr_size = sizeof(new_sockaddr);
    new_socket = accept(socket_fd, (struct sockaddr*)&new_sockaddr, &addr_size);
    if (new_socket < 0) {
        std::cout << "Failed to accept with client." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Connected to a client." << std::endl;
}

void Server::ClientHandling() {
    while (true) {
        int bytes = recv(new_socket, buf, sizeof(buf), 0);
        if (bytes < 0) {
            break;
        } else if (bytes == 0) {
            std::cout << "Client disconnected." << std::endl;
            break;
        } else {
            buf[bytes] = '\0';
            std::cout << "Client: " << buf << std::endl;

            std::cout << "Server: ";
            std::cin.getline(buf, sizeof(buf));
            send(new_socket, buf, strlen(buf), 0);
            memset(buf, 0, sizeof(buf));
        }
    }
    close(new_socket);
}

Server::~Server() {
    close(socket_fd);
}

int main()
{
    int ServerPort = 9999;

    Server server(ServerPort);
    server.Listen();
    server.Accept();
    server.ClientHandling();
}