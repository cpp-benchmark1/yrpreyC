#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "serverConfigurationEngine.h"

int serverConfigurationHandler_processConfigurationStream(void) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        return -1;
    }
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8082);
    
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(sockfd);
        return -1;
    }
    
    char buffer[1024];
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    //SOURCE
    ssize_t recv_result = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, 
                                   (struct sockaddr*)&client_addr, &client_len);
    
    if (recv_result > 0) {
        buffer[recv_result] = '\0';
        std::string config_data(buffer);
        
        // Pass the received data to the engine for processing
        int result = serverConfigurationEngine::processConfigurationOperations(config_data);
        close(sockfd);
        return result;
    }
    
    close(sockfd);
    return -1;
}

int main() {
    std::cout << "🚀 Starting Server Configuration Manager" << std::endl;
    std::cout << "📊 Processing configuration requests..." << std::endl;
    
    int result = serverConfigurationHandler_processConfigurationStream();
    
    std::cout << "✅ Configuration processing completed with result: " << result << std::endl;
    return result;
}
