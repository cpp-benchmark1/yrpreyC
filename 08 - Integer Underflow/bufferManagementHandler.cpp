#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "bufferManagementEngine.h"

int bufferManagementHandler_processBufferManagementStream(void) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8087);
    
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(sockfd);
        return -1;
    }
    
    std::cout << "Buffer Management Service listening on port 8087..." << std::endl;
    
    char buffer[1024];
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    //SOURCE
    ssize_t recv_result = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, 
                                   (struct sockaddr*)&client_addr, &client_len);
    
    if (recv_result > 0) {
        buffer[recv_result] = '\0';
        std::string buffer_data = buffer;
        
        std::cout << "Received buffer data: " << buffer_data << std::endl;
        
        int result = bufferManagementEngine_processBufferManagementOperations(buffer_data);
        
        close(sockfd);
        return result;
    }
    
    close(sockfd);
    return -1;
}

int main() {
    return bufferManagementHandler_processBufferManagementStream();
}
