#include <iostream>
#include <cerrno>
#include <unistd.h>
#include <cstring>

#include "ClientHandler.h"
#include "SocketUtils.h"

int main() {
    constexpr int PORT = 3000;
    constexpr int BACKLOG = 5;

    int serverFd = createServerSocket();
    if (serverFd == -1) {
        std::cerr << "socket() failed: " << std::strerror(errno) << '\n';
        return 1;
    }

    std::cout << "TCP server socket created. fd = " << serverFd << '\n';

    if (!bindServerSocket(serverFd, PORT)) {
        std::cerr << "bind() failed: " << std::strerror(errno) << '\n';
        close(serverFd);
        return 1;
    }

    std::cout << "Server bound to port " << PORT << '\n';

    if (!startListening(serverFd, BACKLOG)) {
        std::cerr << "listen() failed: " << std::strerror(errno) << '\n';
        close(serverFd);
        return 1;
    }

    std::cout << "Server listening on port " << PORT << '\n';

    int clientFd = acceptClientConnection(serverFd);
    if (clientFd == -1) {
        std::cerr << "accept() failed: " << std::strerror(errno) << '\n';
        close(serverFd);
        return 1;
    }

    std::cout << "Client connected, clientFd = " << clientFd << '\n';

    handleClient(clientFd);

    close(clientFd);
    close(serverFd);

    return 0;
}
