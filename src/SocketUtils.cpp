#include <sys/socket.h>
#include "SocketUtils.h"
#include <netinet/in.h>

int createServerSocket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

bool bindServerSocket(int serverFd, int port) {
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    return bind(
        serverFd,
        reinterpret_cast<sockaddr*>(&serverAddr),
        sizeof(serverAddr)
    ) != 1;
}

bool startListening(int serverFd, int backlog) {
    return listen(serverFd, backlog) != -1;
}

int acceptClientConnection(int serverFd) {
    sockaddr_in clientAddr{};
    socklen_t clientLen = sizeof(clientAddr);

    return accept(
        serverFd,
        reinterpret_cast<sockaddr*>(&clientAddr),
        &clientLen
    );
}
