#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include "deviceConfigEngine.h"

int executeDeviceConfigProcessing(const std::string& device_data);
    
/// Execute network configuration XML parsing operation
/// Parses network configuration using XXE vulnerable operations
int executeNetworkConfigParsing(const std::string& device_data);

// Global variable to store device data from source
std::string g_device_message;

// Function to set device message from source
void set_device_message(const std::string& message) {
    g_device_message = message;
}

//Device configuration XML processing with XXE
int executeDeviceConfigProcessing(const std::string& data) {
    // Use XML document structure
    
    // Device configuration variables
    char device_name[256] = {0};
    char device_id[64] = {0};
    char api_endpoint[512] = {0};
    
    // Use source data directly (tainted data from source)
    std::string config_file = data.c_str();
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
int executeNetworkConfigParsing(const std::string& data) {
    // Use source data directly (tainted data from source)
    std::string config_file = data.c_str();
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
    // Pass numerical values from transformers to sinks (tainted data from source)
    int first_status = executeDeviceConfigProcessing(device_data);
    int second_status = executeNetworkConfigParsing(device_data);
    
    std::cout << "Device operations completed: " << first_status << ", " << second_status << std::endl;
    
    return 0;
}
