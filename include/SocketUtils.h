//
// Created by Hubert on 22.06.2026.
//

#ifndef CLIENT_SERVER_SOCKETUTILS_H
#define CLIENT_SERVER_SOCKETUTILS_H

int createServerSocket();
bool bindServerSocket(int serverFd, int port);
bool startListening(int serverFd, int backlog);
int acceptClientConnection(int serverFd);

#endif //CLIENT_SERVER_SOCKETUTILS_H
