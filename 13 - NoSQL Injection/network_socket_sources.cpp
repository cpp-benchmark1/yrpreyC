#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "unicode_processor.cpp"
#include "unicode_search_engine.cpp"

#pragma comment(lib, "ws2_32.lib")

void processNetworkData()
{
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return;
    }

    // First source: recvfrom
    {
        SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock != INVALID_SOCKET) {
            struct sockaddr_in srv;
            memset(&srv, 0, sizeof(srv));
            srv.sin_family = AF_INET;
            srv.sin_port = htons(12349);
            inet_pton(AF_INET, "127.0.0.1", &srv.sin_addr);

            if (connect(sock, (struct sockaddr*)&srv, sizeof(srv)) == 0) {
                char buf[4096];
                struct sockaddr_in fromAddr;
                int fromLen = sizeof(fromAddr);

                //SOURCE
                int bytesReceived = recvfrom(sock, buf, sizeof(buf) - 1, 0,
                    (struct sockaddr*)&fromAddr, &fromLen);
                
                if (bytesReceived > 0) {
                    buf[bytesReceived] = '\0';
                    // Call first NoSQL injection sink
                    UnicodeCategoryProcessor::processCategoryUpdate(buf, bytesReceived);
                }
            }
            closesocket(sock);
        }
    }

    // Second source: read
    {
        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock != INVALID_SOCKET) {
            struct sockaddr_in srv;
            memset(&srv, 0, sizeof(srv));
            srv.sin_family = AF_INET;
            srv.sin_port = htons(12349);
            inet_pton(AF_INET, "127.0.0.1", &srv.sin_addr);

            if (connect(sock, (struct sockaddr*)&srv, sizeof(srv)) == 0) {
                char buf[4096];

                //SOURCE
                int bytesReceived = recv(sock, buf, sizeof(buf) - 1, 0);
                
                if (bytesReceived > 0) {
                    buf[bytesReceived] = '\0';
                    // Call second NoSQL injection sink
                    UnicodeSearchEngine::searchUnicodeCategories(buf, bytesReceived);
                }
            }
            closesocket(sock);
        }
    }

    // Cleanup Winsock
    WSACleanup();
} 