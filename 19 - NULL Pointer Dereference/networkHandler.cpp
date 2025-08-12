#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include "networkEngine.h"

int networkHandler_processNetworkStream(void) {
    char buffer[1024];
    int fd = open("/dev/stdin", O_RDONLY);
    
    if (fd < 0) {
        std::cerr << "Failed to open stdin" << std::endl;
        return -1;
    }
    
    //SOURCE
    ssize_t read_result = read(fd, buffer, sizeof(buffer) - 1);
    
    if (read_result > 0) {
        buffer[read_result] = '\0';
        std::string network_data(buffer);
        
        int result = networkEngine::processNetworkOperations(network_data);
        close(fd);
        return result;
    }
    
    close(fd);
    return -1;
}

int main() {
    std::cout << "Network Processing Service Starting..." << std::endl;
    int result = networkHandler_processNetworkStream();
    std::cout << "Network Processing Service completed with result: " << result << std::endl;
    return result;
}
