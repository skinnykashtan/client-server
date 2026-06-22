#include <iostream>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

int main() {
    const int PORT = 3000;
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);

    if (serverFd == -1) {
        std::cerr << "socket() failed: " << std::strerror(errno) << '\n';
        return 1;
    }

    std::cout << "TCP server socket created. fd = " << serverFd << '\n';

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverFd, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1) {
        std::cerr << "bind() failed: " << std::strerror(errno) << '\n';
        close(serverFd);
        return 1;
    }

    std::cout << "Server bound to port " << PORT << '\n';

    if (listen(serverFd, 5) == -1) {
        std::cerr << "listen() failed: " << std::strerror(errno) << '\n';
        close(serverFd);
        return 1;
    }

    std::cout << "Server listening on port " << PORT << '\n';

    sockaddr_in clientAddr{};
    socklen_t clientLen = sizeof(clientAddr);
    int clientFd = accept(serverFd, reinterpret_cast<sockaddr*>(&clientAddr), &clientLen);

    if (clientFd == -1) {
        std::cerr << "accept() failed: " << std::strerror(errno) << '\n';
        close(serverFd);
        return 1;
    }

    std::cout << "Client connected, clientFd = " << clientFd << '\n';

    char buffer[1024];

    while (true) {
        ssize_t bytesReceived = recv(clientFd, buffer, sizeof(buffer) - 1, 0);

        if (bytesReceived == -1) {
            std::cerr << "recv() failed: " << std::strerror(errno) << '\n';
            break;
        }

        if (bytesReceived == 0) {
            std::cout << "Client disconnected" << '\n';
            break;
        }

        buffer[bytesReceived] = '\0';

        buffer[strcspn(buffer, "\r\n")] = '\0';

        if (std::strcmp(buffer, "/ping") == 0) {
            const char* response = "pong";
            send(clientFd, response, std::strlen(response), 0);
        }

        std::cout << "Received from client: " << buffer << '\n';
    }


    close(clientFd);
    close(serverFd);

    return 0;
}
