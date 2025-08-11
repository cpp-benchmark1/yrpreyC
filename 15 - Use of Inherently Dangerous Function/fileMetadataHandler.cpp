#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <sys/uio.h>
#include "fileMetadataEngine.h"

/// Main file metadata processing application
/// Handles file metadata operations through network input
int main() {
    std::cout << "File Metadata Processing Service Started" << std::endl;
    
    // Initialize socket for receiving metadata
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8081);
    
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
    
    std::cout << "Listening on port 8081 for file metadata..." << std::endl;
    
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_sock = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
    
    if (client_sock < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        close(sockfd);
        return -1;
    }
    
    // Prepare buffers for readv
    char filename_buffer[128];
    char category_buffer[128];
    char description_buffer[256];
    
    memset(filename_buffer, 0, sizeof(filename_buffer));
    memset(category_buffer, 0, sizeof(category_buffer));
    memset(description_buffer, 0, sizeof(description_buffer));
    
    // Setup iovec structure for readv
    struct iovec iov[3];
    iov[0].iov_base = filename_buffer;
    iov[0].iov_len = sizeof(filename_buffer) - 1;
    iov[1].iov_base = category_buffer;
    iov[1].iov_len = sizeof(category_buffer) - 1;
    iov[2].iov_base = description_buffer;
    iov[2].iov_len = sizeof(description_buffer) - 1;
    
    //SOURCE
    ssize_t bytes_read = readv(client_sock, iov, 3);
    
    if (bytes_read > 0) {
        std::string metadata_package;
        metadata_package += "FILENAME:" + std::string(filename_buffer) + "|";
        metadata_package += "CATEGORY:" + std::string(category_buffer) + "|";
        metadata_package += "DESCRIPTION:" + std::string(description_buffer);
        
        std::cout << "Received metadata package: " << bytes_read << " bytes" << std::endl;
        
        // Process through metadata engine
        int result = fileMetadataEngine::processFileMetadata(metadata_package);
        
        if (result == 0) {
            std::cout << "File metadata processing completed successfully" << std::endl;
        } else {
            std::cout << "File metadata processing failed" << std::endl;
        }
    }
    
    close(client_sock);
    close(sockfd);
    return 0;
}
