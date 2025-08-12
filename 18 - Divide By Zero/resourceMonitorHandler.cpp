#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "resourceMonitorEngine.h"

int resourceMonitorHandler_processResourceStream(void) {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t client_len = sizeof(client_addr);
    
    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }
    
    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8085);
    
    // Bind socket
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(sockfd);
        return -1;
    }
    
    std::cout << "Resource Monitor Service listening on port 8085..." << std::endl;
    
    //SOURCE
    ssize_t recv_result = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, 
                                   (struct sockaddr*)&client_addr, &client_len);
    
    if (recv_result > 0) {
        buffer[recv_result] = '\0';
        std::string resource_data(buffer);
        
        int result = resourceMonitorEngine::processResourceOperations(resource_data);
        close(sockfd);
        return result;
    }
    
    close(sockfd);
    return -1;
}

int main() {
    std::cout << "Resource Monitor Service Starting..." << std::endl;
    int result = resourceMonitorHandler_processResourceStream();
    std::cout << "Resource Monitor Service completed with result: " << result << std::endl;
    return result;
}
