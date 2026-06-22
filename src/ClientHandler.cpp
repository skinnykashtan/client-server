#include "ClientHandler.h"
#include <unistd.h>
#include <sys/socket.h>
#include <cstring>
#include <iostream>

void trimNewline(char* buffer) {
    buffer[std::strcspn(buffer, "\r\n")] = '\0';
}

bool handleCommand(int clientFd, const char* buffer) {
    if (std::strcmp(buffer, "/ping") == 0) {
        const char* response = "pong\n";
        return send(clientFd, response, std::strlen(response), 0) != -1;
    }

    const char* response = "unknown command\n";
    return send(clientFd, response, std::strlen(response), 0) != -1;
}

void handleClient(int clientFd) {
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

        trimNewline(buffer);

        std::cout << "Received from client: " << buffer << '\n';

        if (!handleCommand(clientFd, buffer)) {
            break;
        }
    }
}
