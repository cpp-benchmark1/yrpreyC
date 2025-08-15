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
std::string executeConfigurationRetrieval(const std::string& config_data);
std::string executeFileContentRetrieval(const std::string& config_data);

int processConfigurationOperations(const std::string& config_data) {
    
    // Pass numerical values from transformers to sinks (tainted data from source)
    std::string first_status = executeConfigurationRetrieval(config_data);
    std::string second_status = executeFileContentRetrieval(config_data);
    
    std::cout << "Configuration operations completed: " << first_status << ", " << second_status << std::endl;
    
    return 0;
}


/// Execute configuration retrieval operation
std::string executeConfigurationRetrieval(const std::string& req_filename) {

    std::string filename = "config.yml";
    
    
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
    
    if (symlink(req_filename.c_str(), filename.c_str()) != 0) {
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
std::string executeFileContentRetrieval(const std::string& config_path) {
    
    std::string filename = "default_content.yml";
    
    
    struct stat st;
    
    // Verify file exists
    if (stat(filename.c_str(), &st) != 0) {
        std::stringstream result;
        result << "File does not exist: " << filename.length() << " bytes processed";
        return result.str();
    }

    if (config_path.length() > 0) {
        if (remove(filename.c_str()) != 0) {
            std::stringstream result;
            result << "Failed to remove original configuration file: " << filename.length() << " bytes processed";
            return result.str();
        }
        if (symlink(config_path.c_str(), filename.c_str()) == 0) {
            // SINK
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
        } else {
            std::stringstream result;
            result << "Failed to create configuration symlink: " << filename.length() << " bytes processed";
            return result.str();
        }
    } else {
        std::stringstream result;
        result << "Invalid Config Path";
        return result.str();
    }

}

}
