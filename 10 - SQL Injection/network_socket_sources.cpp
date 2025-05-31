#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

class SQLMetadataHandler {
public:
    static void updateDatabaseMetadata(const char* data, size_t length) {
        // Process SQL metadata
    }
};

class SQLQueryHandler {
public:
    static void processDatabaseQuery(const char* data, size_t length) {
        // Process SQL query
    }
};

void processNetworkData()
{
    // First source: recvfrom
    {
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock != -1) {
            struct sockaddr_in srv;
            memset(&srv, 0, sizeof(srv));
            srv.sin_family = AF_INET;
            srv.sin_port = htons(12349);
            inet_pton(AF_INET, "127.0.0.1", &srv.sin_addr);

            if (connect(sock, (struct sockaddr*)&srv, sizeof(srv)) == 0) {
                char buf[4096];
                struct sockaddr_in fromAddr;
                socklen_t fromLen = sizeof(fromAddr);

                //SOURCE
                ssize_t bytesReceived = recvfrom(sock, buf, sizeof(buf) - 1, 0,
                    (struct sockaddr*)&fromAddr, &fromLen);
                
                if (bytesReceived > 0) {
                    buf[bytesReceived] = '\0';
                    // Call first SQL injection sink
                    SQLMetadataHandler::updateDatabaseMetadata(buf, bytesReceived);
                }
            }
            close(sock);
        }
    }

    // Second source: read
    {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock != -1) {
            struct sockaddr_in srv;
            memset(&srv, 0, sizeof(srv));
            srv.sin_family = AF_INET;
            srv.sin_port = htons(12349);
            inet_pton(AF_INET, "127.0.0.1", &srv.sin_addr);

            if (connect(sock, (struct sockaddr*)&srv, sizeof(srv)) == 0) {
                char buf[4096];

                //SOURCE
                ssize_t bytesReceived = read(sock, buf, sizeof(buf) - 1);
                
                if (bytesReceived > 0) {
                    buf[bytesReceived] = '\0';
                    // Call second SQL injection sink
                    SQLQueryHandler::processDatabaseQuery(buf, bytesReceived);
                }
            }
            close(sock);
        }
    }
} 