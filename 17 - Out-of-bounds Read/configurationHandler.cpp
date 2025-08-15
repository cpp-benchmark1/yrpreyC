#include <iostream>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include "configurationEngine.h"
#include "configurationHandler.h"

int configurationHandler_processConfigurationStream(void) {
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
        std::string config_data(buffer);
        
        int result = configurationEngine::processConfigurationOperations(config_data);
        close(fd);
        return result;
    }
    
    close(fd);
    return -1;
}

int main() {
    std::cout << "Configuration Processing Service Starting..." << std::endl;
    int result = configurationHandler_processConfigurationStream();
    std::cout << "Configuration Processing Service completed with result: " << result << std::endl;
    return result;
}
