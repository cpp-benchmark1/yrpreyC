#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include "configurationEngine.h"
#include "configurationHandler.h"
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int configurationHandler_processConfigurationStream(void) {
    const int PORT = 5002;
    int sockfd;
    struct sockaddr_in server_addr{}, client_addr{};
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create UDP socket" << std::endl;
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind UDP socket" << std::endl;
        close(sockfd);
        return -1;
    }

    //SOURCE
    ssize_t read_result = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&client_addr, &client_len);

    if (read_result > 0) {
        buffer[read_result] = '\0';
        std::string config_data(buffer);
        
        int result = configurationEngine::processConfigurationOperations(config_data);
        close(sockfd);
        return result;
    }

    close(sockfd);
    return -1;
}

int main() {
    std::cout << "Configuration Processing Service Starting..." << std::endl;
    int result = configurationHandler_processConfigurationStream();
    std::cout << "Configuration Processing Service completed with result: " << result << std::endl;
    return result;
}
