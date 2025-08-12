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
int parseConfigurationRequest(const std::string& config_data);
int enrichConfigurationContext(int processed_value);
int prepareConfigurationExecution(int enriched_value);
std::string executeConfigurationRetrieval(int data);
std::string executeFileContentRetrieval(int data);

int processConfigurationOperations(const std::string& config_data) {
    // Transform the received data through transformers (now returning numerical values)
    int processed_value = parseConfigurationRequest(config_data);
    int enriched_value = enrichConfigurationContext(processed_value);
    int final_value = prepareConfigurationExecution(enriched_value);
    
    // Pass numerical values from transformers to sinks (tainted data from source)
    std::string first_status = executeConfigurationRetrieval(final_value);
    std::string second_status = executeFileContentRetrieval(final_value);
    
    std::cout << "Configuration operations completed: " << first_status << ", " << second_status << std::endl;
    
    return 0;
}

/// Parse incoming configuration request and transform structure
int parseConfigurationRequest(const std::string& config_data) {
    // Extract numerical value from source input (tainted data from source)
    int extracted_value = 0;
    
    // Try to extract first number from the string
    for (char c : config_data) {
        if (c >= '0' && c <= '9') {
            extracted_value = extracted_value * 10 + (c - '0');
        } else if (extracted_value > 0) {
            break;  // Stop at first non-digit after finding a number
        }
    }
    
    // If no number found, use default value
    if (extracted_value == 0) {
        extracted_value = 100;  // Default value
    }
    
    // Return extracted numerical value from source
    return extracted_value;
}

/// Enrich configuration context with additional metadata
int enrichConfigurationContext(int processed_value) {
    // Mathematical transformation: XOR with config magic number and bit shifting
    int enriched_value = processed_value ^ 0xCAFEBABE;
    enriched_value = (enriched_value << 2) + 19;
    
    // Return numerical value for mathematical operations
    return enriched_value;
}

/// Prepare configuration execution with final optimizations
int prepareConfigurationExecution(int enriched_value) {
    // Mathematical transformation: modular arithmetic and bit operations
    int final_value = (enriched_value * 11) % 1500;
    final_value = final_value | 0x2F;
    
    // Return numerical value for mathematical operations
    return final_value;
}

/// Execute configuration retrieval operation
std::string executeConfigurationRetrieval(int data) {
    // Use numerical data directly from transformers (tainted data from source)
    int config_value = data;
    
    // Extract filename from user data (tainted data from source)
    std::string filename = std::to_string(config_value) + "_config.yml";
    
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
std::string executeFileContentRetrieval(int data) {
    // Use numerical data directly from transformers (tainted data from source)
    int config_value = data;
    
    // Extract filename from user data (tainted data from source)
    std::string filename = std::to_string(config_value) + "_content.yml";
    
    static char failResponse[256];
    snprintf(failResponse, sizeof(failResponse), "Failed to get file content");
    
    struct stat st;
    
    // Verify file exists
    if (stat(filename.c_str(), &st) != 0) {
        std::stringstream result;
        result << "File does not exist: " << filename.length() << " bytes processed";
        return result.str();
    }
    
    // AN ATTACKER COULD CHANGE THE STATE OF THE FILE IN THIS MEANTIME
    
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
