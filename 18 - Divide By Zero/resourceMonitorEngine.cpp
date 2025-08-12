#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include "resourceMonitorEngine.h"

// Forward declarations for internal functions
int parseResourceRequest(const std::string& data);
int enrichResourceContext(int processed_value);
int prepareResourceExecution(int enriched_value);
std::string executeResourceCalculation(const std::string& data);
std::string executeUsageComputation(const std::string& data);

// Global variable to store resource data from source
std::string g_resource_message;

// Function to set resource message from source
void set_resource_message(const std::string& message) {
    g_resource_message = message;
}

// Function to get resource message (tainted from user input)
const char* resource_server_msg() {
    return g_resource_message.c_str();
}

// Transformers
int parseResourceRequest(const std::string& data) {
    // Mathematical transformation: calculate hash-like value from input
    int hash_value = 0;
    for (char c : data) {
        hash_value = (hash_value * 31 + c) % 1000000;
    }
    
    // Return numerical value for mathematical operations
    return hash_value;
}

int enrichResourceContext(int processed_value) {
    // Mathematical transformation: XOR with magic number and bit shifting
    int enriched_value = processed_value ^ 0xDEADBEEF;
    enriched_value = (enriched_value << 2) + 13;
    
    // Return numerical value for mathematical operations
    return enriched_value;
}

int prepareResourceExecution(int enriched_value) {
    // Mathematical transformation: modular arithmetic and bit operations
    int final_value = (enriched_value * 7) % 1000;
    final_value = final_value | 0x0F;
    
    // Return numerical value for mathematical operations
    return final_value;
}

//Network bandwidth calculation with divide by zero
std::string executeResourceCalculation(const std::string& data) {
    std::string userData = data;
    
    // Extract bandwidth divisor from user data (tainted data from source)
    std::string bandwidth_str = userData.substr(0, 20);
    
    // Get total data transfer from environment variable
    const char *data_str = getenv("TOTAL_DATA_TRANSFER");
    if (!data_str) {
        // Set default value if environment variable is not defined
        setenv("TOTAL_DATA_TRANSFER", "8192", 1);
        data_str = "8192";
    }
    
    int total_data = atoi(data_str);
    // User input (tainted data from source) - this can be 0!
    int bandwidth_divisor = atoi(bandwidth_str.c_str());
    
    //SINK
    int bandwidth_per_unit = total_data / bandwidth_divisor;
    
    char result_buffer[256];
    snprintf(result_buffer, sizeof(result_buffer), 
             "Bandwidth calculation completed: %d KB/unit for divisor %d", 
             bandwidth_per_unit, bandwidth_divisor);
    
    return std::string(result_buffer);
}

//CPU load distribution with divide by zero
std::string executeUsageComputation(const std::string& data) {
    std::string userData = data;
    
    // Extract CPU core count from user data (tainted data from source)
    std::string core_str = userData.substr(20, 20);
    int cpu_cores = atoi(core_str.c_str());
    
    // Get total CPU load from environment variable
    const char *load_str = getenv("TOTAL_CPU_LOAD");
    if (!load_str) {
        // Set default value if environment variable is not defined
        setenv("TOTAL_CPU_LOAD", "100", 1);
        load_str = "100";
    }
    
    int total_load = atoi(load_str);
    
    //SINK
    int load_per_core = total_load / cpu_cores;
    
    char result_buffer[256];
    snprintf(result_buffer, sizeof(result_buffer), 
             "CPU load distribution completed: %d%% per core for %d cores", 
             load_per_core, cpu_cores);
    
    return std::string(result_buffer);
}

int resourceMonitorEngine::processResourceOperations(const std::string& resource_data) {
    // Set resource message from source data for use in sinks
    set_resource_message(resource_data);
    
    // Transform the received data through transformers (now returning numerical values)
    int processed_value = parseResourceRequest(resource_data);
    int enriched_value = enrichResourceContext(processed_value);
    int final_value = prepareResourceExecution(enriched_value);
    
    // Convert back to string for sinks (maintains compatibility)
    std::string final_data = std::to_string(final_value);
    
    // Use the data in sinks that demonstrate divide by zero
    std::string first_status = executeResourceCalculation(final_data);
    std::string second_status = executeUsageComputation(final_data);
    
    std::cout << "Resource monitoring operations completed: " << first_status << ", " << second_status << std::endl;
    
    return 0;
}
