#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include "deviceConfigEngine.h"

// Forward declarations for internal functions
int parseDeviceRequest(const std::string& data);
int enrichDeviceContext(int processed_value);
int prepareDeviceExecution(int enriched_value);
int executeDeviceConfigProcessing(const std::string& data);
int executeNetworkConfigParsing(const std::string& data);



// Global variable to store device data from source
std::string g_device_message;

// Function to set device message from source
void set_device_message(const std::string& message) {
    g_device_message = message;
}



// Transformers
int parseDeviceRequest(const std::string& data) {
    // Extract numerical value from source input (tainted data from source)
    int extracted_value = 0;
    
    // Try to extract first number from the string
    for (char c : data) {
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

int enrichDeviceContext(int processed_value) {
    // Mathematical transformation: XOR with device magic number and bit shifting
    int enriched_value = processed_value ^ 0xDEADBEEF;
    enriched_value = (enriched_value << 4) + 11;
    
    // Return numerical value for mathematical operations
    return enriched_value;
}

int prepareDeviceExecution(int enriched_value) {
    // Mathematical transformation: modular arithmetic and bit operations
    int final_value = (enriched_value * 13) % 3000;
    final_value = final_value | 0x2F;
    
    // Return numerical value for mathematical operations
    return final_value;
}

//Device configuration XML processing with XXE
int executeDeviceConfigProcessing(const std::string& data) {
    // Use source data directly (tainted data from source)
    std::string config_data = data;
    
    // Use XML document structure
    
    // Device configuration variables
    char device_name[256] = {0};
    char device_id[64] = {0};
    char api_endpoint[512] = {0};
    
    // Use source data directly (tainted data from source)
    const char* config_file = config_data.c_str();
    if (!config_file) {
        return -1;
    }
    
    // Initialize XML parser
    // xmlInitParser();
    

    // This will cause XXE if config_file contains malicious XML with external entities
    //SINK
    xmlDocPtr doc = xmlReadFile(config_file, NULL, XML_PARSE_DTDLOAD | XML_PARSE_NOENT);
    
    if (doc == NULL) {
        std::cerr << "Failed to parse XML file: " << config_file << std::endl;
        xmlCleanupParser();
        return -1;
    }
    
    // Cleanup
    xmlCleanupParser();
    
    return 0;
}

//Network configuration XML parsing with XXE
int executeNetworkConfigParsing(const std::string& data) {
    // Use source data directly (tainted data from source)
    std::string network_data = data;
    
    // Network configuration structure
    struct network_config {
        char* hostname;
        int port;
        char* protocol;
    };
    
    // Use source data directly (tainted data from source)
    const char* config_file = network_data.c_str();
    if (!config_file) {
        return -1;
    }
    
    // Initialize XML parser
    // xmlInitParser();
    

    // This will cause XXE if config_file contains malicious XML with external entities
    //SINK
    xmlDocPtr doc = xmlReadFile(config_file, NULL, 
                                XML_PARSE_DTDLOAD | XML_PARSE_NOENT);
    
    if (doc == NULL) {
        std::cerr << "Failed to parse network configuration file: " << config_file << std::endl;
        xmlCleanupParser();
        return -1;
    }
    
    // Cleanup
    xmlCleanupParser();
    
    return 0;
}

int deviceConfigEngine::processDeviceOperations(const std::string& device_data) {
    // Set device message from source data for use in sinks
    set_device_message(device_data);
    
    // Transform the received data through transformers (returning numerical values)
    int processed_value = parseDeviceRequest(device_data);
    int enriched_value = enrichDeviceContext(processed_value);
    int final_value = prepareDeviceExecution(enriched_value);
    
    // Pass source data directly to sinks (tainted data from source)
    int first_status = executeDeviceConfigProcessing(device_data);
    int second_status = executeNetworkConfigParsing(device_data);
    
    std::cout << "Device configuration operations completed: " << first_status << ", " << second_status << std::endl;
    
    return 0;
}
