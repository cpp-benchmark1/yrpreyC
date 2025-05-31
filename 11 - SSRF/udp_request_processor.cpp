#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

class UDPRequestHandler {
public:
    static void processUDPRequest(const char* buffer, size_t size)
    {
        // First transformation: Parse network configuration
        char target[128] = {0};
        char portStr[8] = {0};
        int port = 12349;  // Default port
        char protocol[8] = "udp";
        
        // Extract protocol and address
        const char* protoPtr = strstr(buffer, "://");
        if (protoPtr) {
            strncpy(protocol, buffer, protoPtr - buffer);
            buffer = protoPtr + 3;
        }
        
        // Extract address and port
        const char* colonPtr = strchr(buffer, ':');
        if (colonPtr) {
            strncpy(portStr, colonPtr + 1, sizeof(portStr) - 1);
            port = atoi(portStr);  // Vulnerable: No validation
            strncpy(target, buffer, colonPtr - buffer);
        } else {
            strncpy(target, buffer, sizeof(target) - 1);
        }

        // Second transformation: Build dynamic message format
        char msg[256] = {0};
        char msgType[32] = "CONNECT";
        
        // Extract message type from input
        if (size > 8) {
            strncpy(msgType, buffer + 8, 7);
            msgType[7] = '\0';
        }
        
        // Build message with type and content
        snprintf(msg, sizeof(msg), "%s %s", msgType, buffer);  // Vulnerable: Direct use of user input

        int sockfd;
        struct sockaddr_in dest_addr;

        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) {
            return;
        }

        memset(&dest_addr, 0, sizeof(dest_addr));
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(static_cast<uint16_t>(port));

        // Vulnerable: Direct use of user input for address
        if (inet_pton(AF_INET, target, &dest_addr.sin_addr) <= 0) {
            close(sockfd);
            return;
        }

        //SINK
        sendto(sockfd, msg, strlen(msg), 0, 
            reinterpret_cast<struct sockaddr*>(&dest_addr), sizeof(dest_addr));
        close(sockfd);
    }
}; 