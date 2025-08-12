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
std::string executeLogFileCreation(const std::string& data);
std::string executeBinaryFileCreation(const std::string& data);

int processDataOperations(const std::string& data) {
    // Transform the received data through transformers
    std::string processed_data = parseDataRequest(data);
    std::string enriched_data = enrichDataContext(processed_data);
    std::string final_data = prepareDataExecution(enriched_data);
    
    // Use the data in sinks that demonstrate incorrect permission assignment
    std::string first_status = executeLogFileCreation(final_data);
    std::string second_status = executeBinaryFileCreation(final_data);
    
    std::cout << "Data operations completed: " << first_status << ", " << second_status << std::endl;
    
    return 0;
}

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
std::string executeLogFileCreation(const std::string& data) {
    std::string userData = data;
    
    // Extract data from user input (tainted data from source)
    std::string inputData = userData.substr(0, 100);
    
    // Extract filename from user input (tainted data from source)
    std::string filename = userData.substr(100, 50);
    if (filename.empty()) {
        filename = "default_log";
    }
    
    // Stack-based buffers for processing
    uint8_t decode_buf[32];
    uint8_t transform_buf[64];
    uint8_t filter_buf[128];
    uint8_t encode_buf[64];
    uint8_t final_buf[32];
    char debug_info[16];
    uint32_t local_checksum = 0;
    bool is_valid = false;
    
    char fname[64];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    // Use tainted filename from user input instead of hardcoded path
    snprintf(fname, sizeof(fname), "/var/logs/%s_%04d%02d%02d_%02d%02d%02d.log", 
             filename.c_str(), 
             tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
             tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
    
    //SINK
    int fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (fd != -1) {
        write(fd, inputData.c_str(), inputData.length());
        close(fd);
    }
    
    std::stringstream result;
    result << "Log file creation completed: " << inputData.length() << " bytes processed";
    return result.str();
}

/// Execute binary file creation with unsafe permissions (second sink)
std::string executeBinaryFileCreation(const std::string& data) {
    std::string userData = data;
    
    // Extract data from user input (tainted data from source)
    std::string inputData = userData.substr(50, 100);
    
    // Extract filename from user input (tainted data from source)
    std::string filename = userData.substr(150, 50);
    if (filename.empty()) {
        filename = "default_bin";
    }
    
    // Stack-based buffers for processing
    uint8_t decode_buf[32];
    uint8_t transform_buf[64];
    uint8_t filter_buf[128];
    uint8_t encode_buf[64];
    uint8_t final_buf[32];
    char debug_info[16];
    uint32_t local_checksum = 0;
    bool is_valid = false;
    
    char fname[64];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    // Use tainted filename from user input instead of hardcoded path
    snprintf(fname, sizeof(fname), "/usr/local/bin/%s_%04d%02d%02d_%02d%02d%02d.bin", 
             filename.c_str(), 
             tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
             tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
    
    //SINK
    int fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0777);
    if (fd != -1) {
        write(fd, inputData.c_str(), inputData.length());
        close(fd);
    }
    
    std::stringstream result;
    result << "Binary file creation completed: " << inputData.length() << " bytes processed";
    return result.str();
}

}
