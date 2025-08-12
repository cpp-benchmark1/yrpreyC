#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "cryptographicEngine.h"

int cryptographicHandler_processCryptographicStream(void) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8083);
    
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(sockfd);
        return -1;
    }
    
    std::cout << "🔐 Cryptographic Service listening on port 8083..." << std::endl;
    
    char buffer[1024];
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    //SOURCE
    ssize_t recv_result = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, 
                                   (struct sockaddr*)&client_addr, &client_len);
    
    if (recv_result > 0) {
        buffer[recv_result] = '\0';
        std::string crypto_data(buffer);
        
        std::cout << "📡 Received cryptographic data: " << crypto_data.length() << " bytes" << std::endl;
        
        // Pass the received data to the engine for processing
        int result = cryptographicEngine::processCryptographicOperations(crypto_data);
        close(sockfd);
        return result;
    }
    
    close(sockfd);
    return -1;
}

int main() {
    std::cout << "🚀 Starting Cryptographic Processing Service" << std::endl;
    std::cout << "🔐 Processing cryptographic streams..." << std::endl;
    
    int result = cryptographicHandler_processCryptographicStream();
    
    std::cout << "✅ Cryptographic processing completed with result: " << result << std::endl;
    return result;
}
