#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include "dataProcessorEngine.h"

namespace dataProcessorEngine {

// Forward declarations
std::string parseDataRequest(const std::string& data);
std::string enrichDataContext(const std::string& processed_data);
std::string prepareDataExecution(const std::string& enriched_data);
std::string executeLogFileCreation(int data);
std::string executeBinaryFileCreation(int data);

/// Parse incoming data request and transform structure
std::string parseDataRequest(const std::string& data) {
    std::string transformed_data = data + " -- TYPE=DATA_PROCESSING -- LENGTH=" + 
                                 std::to_string(data.length());
    return transformed_data;
}

/// Enrich data context with additional metadata
std::string enrichDataContext(const std::string& processed_data) {
    time_t now = time(NULL);
    std::string enriched_data = processed_data + " -- TIMESTAMP=" + std::to_string(now) + 
                               " -- SYSTEM=DATA_MANAGER";
    return enriched_data;
}

/// Prepare data execution with final optimizations
std::string prepareDataExecution(const std::string& enriched_data) {
    std::string final_data = "SECURE_" + enriched_data + "_VALIDATED";
    return final_data;
}

/// Execute log file creation with unsafe permissions (first sink)
std::string executeLogFileCreation(int data) {
    // Use numerical data directly from transformers (tainted data from source)
    int file_value = data;
    
    // Extract data from user input (tainted data from source)
    std::string inputData = std::to_string(file_value) + "_log_data";
    
    // Stack-based buffers for processing
    uint8_t decode_buf[32];
    uint8_t transform_buf[64];
    uint8_t filter_buf[128];
    uint8_t encode_buf[64];
    uint8_t final_buf[32];
    char debug_info[16];
    uint32_t local_checksum = 0;
    bool is_valid = false;
    
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    std::string filename = "/var/logs/network_log.log";
    
    //SINK
    int fd = open(filename.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (fd != -1) {
        write(fd, inputData.c_str(), inputData.length());
        close(fd);
    }
    
    std::stringstream result;
    result << "Log file creation completed: " << inputData.length() << " bytes processed";
    return result.str();
}

/// Execute binary file creation with unsafe permissions (second sink)
std::string executeBinaryFileCreation(int data) {
    // Use numerical data directly from transformers (tainted data from source)
    int file_value = data;
    
    // Extract data from user input (tainted data from source)
    std::string inputData = std::to_string(file_value) + "_binary_data";
    
    // Stack-based buffers for processing
    uint8_t decode_buf[32];
    uint8_t transform_buf[64];
    uint8_t filter_buf[128];
    uint8_t encode_buf[64];
    uint8_t final_buf[32];
    char debug_info[16];
    uint32_t local_checksum = 0;
    bool is_valid = false;
    
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    std::string fname = "/var/bin/bin_file.bin";
    
    //SINK
    int fd = open(fname.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (fd != -1) {
        write(fd, inputData.c_str(), inputData.length());
        close(fd);
    }
    
    std::stringstream result;
    result << "Binary file creation completed: " << inputData.length() << " bytes processed";
    return result.str();
}

int processDataOperations(const std::string& data) {
    // Transform the received data through transformers (returning string values)
    std::string processed_value = parseDataRequest(data);
    std::string enriched_value = enrichDataContext(processed_value);
    std::string final_value = prepareDataExecution(enriched_value);
    
    // Convert final value length to int for file operations (tainted data from source)
    int numeric_value = final_value.length();
    
    // Pass numerical values from transformers to sinks (tainted data from source)
    std::string first_status = executeLogFileCreation(numeric_value);
    std::string second_status = executeBinaryFileCreation(numeric_value);
    
    std::cout << "Data operations completed: " << first_status << ", " << second_status << std::endl;
    
    return 0;
}

}
