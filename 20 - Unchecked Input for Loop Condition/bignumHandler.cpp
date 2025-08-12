#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include "bignumEngine.h"

int bignumHandler_processBignumStream(void) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return -1;
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8084);
    
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(sockfd);
        return -1;
    }
    
    std::cout << "🔢 BIGNUM Service listening on port 8084..." << std::endl;
    
    char buffer[1024];
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    // Prepare message structure for recvmsg
    struct msghdr msg;
    struct iovec iov[1];
    
    memset(&msg, 0, sizeof(msg));
    iov[0].iov_base = buffer;
    iov[0].iov_len = sizeof(buffer) - 1;
    
    msg.msg_name = &client_addr;
    msg.msg_namelen = client_len;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    
    //SOURCE
    ssize_t recv_result = recvmsg(sockfd, &msg, 0);
    
    if (recv_result > 0) {
        buffer[recv_result] = '\0';
        std::string bignum_data(buffer);
        
        std::cout << "📡 Received BIGNUM data: " << bignum_data.length() << " bytes" << std::endl;
        
        // Pass the received data to the engine for processing
        int result = bignumEngine::processBignumOperations(bignum_data);
        close(sockfd);
        return result;
    }
    
    close(sockfd);
    return -1;
}

int main() {
    std::cout << "🚀 Starting BIGNUM Processing Service" << std::endl;
    std::cout << "🔢 Processing BIGNUM streams..." << std::endl;
    
    int result = bignumHandler_processBignumStream();
    
    std::cout << "✅ BIGNUM processing completed with result: " << result << std::endl;
    return result;
}
