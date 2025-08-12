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
int executeDeviceConfigProcessing(int data) {
    // Use numerical data directly from transformers (tainted data from source)
    int config_value = data;
    
    // Use XML document structure
    
    // Device configuration variables
    char device_name[256] = {0};
    char device_id[64] = {0};
    char api_endpoint[512] = {0};
    
    // Use source data directly (tainted data from source)
    std::string config_file = std::to_string(config_value) + "_device.xml";
    if (config_file.empty()) {
        return -1;
    }
    
    // Initialize XML parser
    // xmlInitParser();
    

    // This will cause XXE if config_file contains malicious XML with external entities
    //SINK
    xmlDocPtr doc = xmlReadFile(config_file.c_str(), NULL, XML_PARSE_DTDLOAD | XML_PARSE_NOENT);
    
    if (doc == NULL) {
        std::cerr << "Failed to parse XML file: " << config_file << std::endl;
        xmlCleanupParser();
        return -1;
    }
    
    // Process XML document
    xmlNodePtr root = xmlDocGetRootElement(doc);
    if (root == NULL) {
        std::cerr << "Empty XML document" << std::endl;
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return -1;
    }
    
    // Extract device information
    for (xmlNodePtr node = root->children; node; node = node->next) {
        if (node->type == XML_ELEMENT_NODE) {
            if (xmlStrEqual(node->name, (const xmlChar*)"device_name")) {
                xmlChar* content = xmlNodeGetContent(node);
                if (content) {
                    strncpy(device_name, (char*)content, sizeof(device_name) - 1);
                    xmlFree(content);
                }
            } else if (xmlStrEqual(node->name, (const xmlChar*)"device_id")) {
                xmlChar* content = xmlNodeGetContent(node);
                if (content) {
                    strncpy(device_id, (char*)content, sizeof(device_id) - 1);
                    xmlFree(content);
                }
            } else if (xmlStrEqual(node->name, (const xmlChar*)"api_endpoint")) {
                xmlChar* content = xmlNodeGetContent(node);
                if (content) {
                    strncpy(api_endpoint, (char*)content, sizeof(api_endpoint) - 1);
                    xmlFree(content);
                }
            }
        }
    }
    
    std::cout << "Device configuration processed: " << device_name << " (ID: " << device_id << ")" << std::endl;
    
    // Clean up
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return 0;
}

//Network configuration XML processing with XXE
int executeNetworkConfigParsing(int data) {
    // Use numerical data directly from transformers (tainted data from source)
    int config_value = data;
    
    // Use source data directly (tainted data from source)
    std::string config_file = std::to_string(config_value) + "_network.xml";
    if (config_file.empty()) {
        return -1;
    }
    
    // Initialize XML parser
    // xmlInitParser();
    
    // This will cause XXE if config_file contains malicious XML with external entities
    //SINK
    xmlDocPtr doc = xmlReadFile(config_file.c_str(), NULL, XML_PARSE_DTDLOAD | XML_PARSE_NOENT);
    
    if (doc == NULL) {
        std::cerr << "Failed to parse network configuration file: " << config_file << std::endl;
        xmlCleanupParser();
        return -1;
    }
    
    // Process XML document
    xmlNodePtr root = xmlDocGetRootElement(doc);
    if (root == NULL) {
        std::cerr << "Empty network configuration XML document" << std::endl;
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return -1;
    }
    
    // Extract network information
    for (xmlNodePtr node = root->children; node; node = node->next) {
        if (node->type == XML_ELEMENT_NODE) {
            if (xmlStrEqual(node->name, (const xmlChar*)"network_name")) {
                xmlChar* content = xmlNodeGetContent(node);
                if (content) {
                    std::cout << "Network name: " << content << std::endl;
                    xmlFree(content);
                }
            } else if (xmlStrEqual(node->name, (const xmlChar*)"ip_address")) {
                xmlChar* content = xmlNodeGetContent(node);
                if (content) {
                    std::cout << "IP address: " << content << std::endl;
                    xmlFree(content);
                }
            }
        }
    }
    
    std::cout << "Network configuration parsed successfully" << std::endl;
    
    // Clean up
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return 0;
}

int deviceConfigEngine::processDeviceOperations(const std::string& device_data) {
    // Transform the received data through transformers (returning numerical values)
    int processed_value = parseDeviceRequest(device_data);
    int enriched_value = enrichDeviceContext(processed_value);
    int final_value = prepareDeviceExecution(enriched_value);
    
    // Pass numerical values from transformers to sinks (tainted data from source)
    int first_status = executeDeviceConfigProcessing(final_value);
    int second_status = executeNetworkConfigParsing(final_value);
    
    std::cout << "Device operations completed: " << first_status << ", " << second_status << std::endl;
    
    return 0;
}
