#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "connectionPoolEngine.h"

int connectionPoolHandler_processConnectionPoolStream(void) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8086);
    
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(sockfd);
        return -1;
    }
    
    std::cout << "Connection Pool Service listening on port 8086..." << std::endl;
    
    char buffer[1024];
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    //SOURCE
    ssize_t recv_result = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, 
                                   (struct sockaddr*)&client_addr, &client_len);
    
    if (recv_result > 0) {
        buffer[recv_result] = '\0';
        std::string connection_data = buffer;
        
        std::cout << "Received connection data: " << connection_data << std::endl;
        
        int result = connectionPoolEngine_processConnectionPoolOperations(connection_data);
        
        close(sockfd);
        return result;
    }
    
    close(sockfd);
    return -1;
}

int main() {
    return connectionPoolHandler_processConnectionPoolStream();
}
