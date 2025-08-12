#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include "dataProcessorEngine.h"

int dataProcessorHandler_processDataStream(void) {
    int fd = open("/dev/stdin", O_RDONLY);
    if (fd < 0) {
        return -1;
    }
    
    char buffer[1024];
    
    //SOURCE
    // Receive data via read()
    ssize_t read_result = read(fd, buffer, sizeof(buffer) - 1);
    
    if (read_result > 0) {
        buffer[read_result] = '\0';
        std::string data_package(buffer);
        
        // Pass the received data to the engine for processing
        int result = dataProcessorEngine::processDataOperations(data_package);
        close(fd);
        return result;
    }
    
    close(fd);
    return -1;
}

int main() {
    std::cout << "🚀 Starting Data Processing Manager" << std::endl;
    std::cout << "📊 Processing data streams..." << std::endl;
    
    int result = dataProcessorHandler_processDataStream();
    
    std::cout << "✅ Data processing completed with result: " << result << std::endl;
    return result;
}
