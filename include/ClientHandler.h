//
// Created by Hubert on 22.06.2026.
//

#ifndef CLIENT_SERVER_CLIENTHANDLER_H
#define CLIENT_SERVER_CLIENTHANDLER_H

void handleClient(int clientFd);
void trimNewline(char* buffer);
bool handleCommand(const char* buffer);

#endif //CLIENT_SERVER_CLIENTHANDLER_H
