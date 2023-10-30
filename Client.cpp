#include "Client.hpp"

// int main()
// {
//     struct sockaddr_in server_addr;
//     char buf[4096];

//     int client_socket = socket(AF_INET, SOCK_STREAM, 0);

//     if(client_socket == -1){
//         std::cout << "Failed to create client socket " << errno <<std::endl;
//         exit(EXIT_FAILURE);
//     }

//     std::cout << "Created." << std::endl;

//     server_addr.sin_family = AF_INET;
//     server_addr.sin_port = htons(9999);
//     server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

//     if(connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
//     {
        // std::cout << "Failed to connect to server" << std::endl;
//         return 1;
//     }

//     std::cout << "Connected to the server" << std::endl;

//     while(1)
//     {
//         std::cout << "Client: ";
//         std::cin.getline(buf , 4096);

//         send(client_socket, buf, strlen(buf), 0);
//         memset(buf, 0, 4096);

//         if(recv(client_socket, buf, sizeof(buf), 0) < 0)
//             std::cout << "Error while messaging" << std::endl;
//         std::cout << "Server: " << buf << std::endl;
//         memset(buf, 0, 4096);

//     }

//     close(client_socket);
// }


Client::Client(int port) {
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cout << "Failed to create client socket " << errno <<std::endl;
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
}

void Client::Connect() {
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cout << "Failed to connect to server" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Connected to the server." << std::endl;
}

void Client::SendReceive() {
    while (true) {
        std::cout << "Client: ";
        std::cin.getline(buf, sizeof(buf));
        send(client_socket, buf, strlen(buf), 0);
        memset(buf, 0, sizeof(buf));

        int bytes = recv(client_socket, buf, sizeof(buf), 0);
        if (bytes < 0) {
            break;
        } else if (bytes == 0) {
            std::cout << "Server disconnected." << std::endl;
            break;
        } else {
            buf[bytes] = '\0';
            std::cout << "Server: " << buf << std::endl;
            memset(buf, 0, sizeof(buf));
        }
    }
}

Client::~Client() {
    close(client_socket);
}

int main()
{
    int ClientPort = 9999;

    Client client(ClientPort);
    client.Connect();
    client.SendReceive();
}