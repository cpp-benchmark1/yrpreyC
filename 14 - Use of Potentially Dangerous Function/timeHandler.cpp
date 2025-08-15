#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "timeEngine.h"

/// Main time processing application
/// Handles time-related operations through network input
int main() {
    std::cout << "Time Processing Service Started" << std::endl;
    
    // Initialize socket for receiving time data
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
    
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(sockfd);
        return -1;
    }
    
    if (listen(sockfd, 5) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        close(sockfd);
        return -1;
    }
    
    std::cout << "Listening on port 8080..." << std::endl;
    
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_sock = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
    
    if (client_sock < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        close(sockfd);
        return -1;
    }
    
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    
    //SOURCE
    ssize_t bytes_read = read(client_sock, buffer, sizeof(buffer) - 1);
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        std::string time_data(buffer);
        
        int final_time = std::stoi(time_data);
        
        // Process through time engine
        int result = timeEngine::processTimeOperations(final_time);
        
        if (result == 0) {
            std::cout << "Time operations completed successfully" << std::endl;
        } else {
            std::cout << "Time operations failed" << std::endl;
        }
    }
    
    close(client_sock);
    close(sockfd);
    return 0;
}
