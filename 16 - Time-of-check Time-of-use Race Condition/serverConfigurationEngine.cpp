#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include "serverConfigurationEngine.h"

namespace serverConfigurationEngine {

// Forward declarations
std::string parseConfigurationRequest(const std::string& config_data);
std::string enrichConfigurationContext(const std::string& processed_data);
std::string prepareConfigurationExecution(const std::string& enriched_data);
std::string executeConfigurationRetrieval(const std::string& data);
std::string executeFileContentRetrieval(const std::string& data);

int processConfigurationOperations(const std::string& config_data) {
    // Transform the received data through transformers
    std::string processed_data = parseConfigurationRequest(config_data);
    std::string enriched_data = enrichConfigurationContext(processed_data);
    std::string final_data = prepareConfigurationExecution(enriched_data);
    
    // Use the data in sinks that demonstrate race condition
    std::string first_status = executeConfigurationRetrieval(final_data);
    std::string second_status = executeFileContentRetrieval(final_data);
    
    std::cout << "Configuration operations completed: " << first_status << ", " << second_status << std::endl;
    
    return 0;
}

/// Parse incoming configuration request and transform structure
std::string parseConfigurationRequest(const std::string& config_data) {
    std::string transformed_data = config_data + " -- TYPE=CONFIGURATION_OPERATION -- LENGTH=" + 
                                 std::to_string(config_data.length());
    return transformed_data;
}

/// Enrich configuration context with additional metadata
std::string enrichConfigurationContext(const std::string& processed_data) {
    time_t now = time(NULL);
    std::string enriched_data = processed_data + " -- TIMESTAMP=" + std::to_string(now) + 
                               " -- SYSTEM=CONFIGURATION_MANAGER";
    return enriched_data;
}

/// Prepare configuration execution with final optimizations
std::string prepareConfigurationExecution(const std::string& enriched_data) {
    std::string final_data = "SECURE_" + enriched_data + "_VALIDATED";
    return final_data;
}

/// Execute configuration retrieval operation
std::string executeConfigurationRetrieval(const std::string& data) {
    std::string userData = data;
    
    // Extract filename from user data (tainted data from source)
    std::string filename = userData.substr(0, 50);
    
    static char failResponse[256];
    snprintf(failResponse, sizeof(failResponse), "Failed to get server configuration");
    
    struct stat st;
    
    // Verify file exists
    if (stat(filename.c_str(), &st) != 0) {
        std::stringstream result;
        result << "Configuration file does not exist: " << filename.length() << " bytes processed";
        return result.str();
    }
    
    // Update configuration file
    if (remove(filename.c_str()) != 0) {
        std::stringstream result;
        result << "Failed to remove original configuration file: " << filename.length() << " bytes processed";
        return result.str();
    }
    
    if (symlink(filename.c_str(), filename.c_str()) != 0) {
        std::stringstream result;
        result << "Failed to create configuration symlink: " << filename.length() << " bytes processed";
        return result.str();
    }
    
    // Read configuration
    //SINK
    FILE *f = fopen(filename.c_str(), "r");
    if (!f) {
        std::stringstream result;
        result << "Failed to open configuration file for reading: " << filename.length() << " bytes processed";
        return result.str();
    }
    
    fclose(f);
    std::stringstream result;
    result << "Configuration retrieval completed: " << filename.length() << " bytes processed";
    return result.str();
}

/// Execute file content retrieval operation
std::string executeFileContentRetrieval(const std::string& data) {
    std::string userData = data;
    
    // Extract filename from user data (tainted data from source)
    std::string filename = userData.substr(50, 50);
    
    static char failResponse[256];
    snprintf(failResponse, sizeof(failResponse), "Failed to get file content");
    
    struct stat st;
    
    // Verify file exists
    if (stat(filename.c_str(), &st) != 0) {
        std::stringstream result;
        result << "File does not exist: " << filename.length() << " bytes processed";
        return result.str();
    }
    
    // Read file content
    //SINK
    FILE *f = fopen(filename.c_str(), "r");
    if (!f) {
        std::stringstream result;
        result << "Failed to open file for reading: " << filename.length() << " bytes processed";
        return result.str();
    }
    
    fclose(f);
    std::stringstream result;
    result << "File content retrieval completed: " << filename.length() << " bytes processed";
    return result.str();
}

}
