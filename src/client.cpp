#include <iostream>
#include <sys/socket.h>
#include "SocketUtils.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <unistd.h>


int main() {
    int clientFd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientFd == -1) {
        std::cerr << "socket() failed: " << std::strerror(errno) << '\n';
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(3000);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(clientFd, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) {
        std::cerr << "connect() failed: " << std::strerror(errno) << '\n';
        close(clientFd);
        return 1;
    }

    std::cout << "Connected to server clientFd: " << clientFd << '\n';

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        send(clientFd, buffer, std::strlen(buffer), 0);

        ssize_t bytesReceived = recv(clientFd, buffer, sizeof(buffer) - 1, 0);

        if (bytesReceived == -1) {
            std::cerr << "recv() failed: " << std::strerror(errno) << '\n';
            break;
        }
        if (bytesReceived == 0) {
            std::cout << "Server disconnected\n";
            break;
        }

        std::cout << buffer << '\n';
    }

    close(clientFd);


    return 0;
}