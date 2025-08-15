#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include "resourceMonitorEngine.h"

namespace resourceMonitorEngine {

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


//Network bandwidth calculation with divide by zero
std::string executeResourceCalculation(int data) {
    // Use numerical data directly from transformers (tainted data from source)
    int bandwidth_divisor = data;
    
    // Get total data transfer from environment variable
    const char *data_str = getenv("TOTAL_DATA_TRANSFER");
    if (!data_str) {
        // Set default value if environment variable is not defined
        setenv("TOTAL_DATA_TRANSFER", "8192", 1);
        data_str = "8192";
    }
    
    int total_data = atoi(data_str);
    // User input (tainted data from source) - this can be 0!
    
    //SINK
    int bandwidth_per_unit = total_data / bandwidth_divisor;
    
    char result_buffer[256];
    snprintf(result_buffer, sizeof(result_buffer), 
             "Bandwidth calculation completed: %d KB/unit for divisor %d", 
             bandwidth_per_unit, bandwidth_divisor);
    
    return std::string(result_buffer);
}

//CPU load distribution with divide by zero
std::string executeUsageComputation(int data) {
    // Use numerical data directly from transformers (tainted data from source)
    int cpu_cores = data;
    
    // Get total CPU load from environment variable
    const char *load_str = getenv("TOTAL_CPU_LOAD");
    if (!load_str) {
        // Set default value if environment variable is not defined
        setenv("TOTAL_CPU_LOAD", "100", 1);
        load_str = "100";
    }
    
    int total_load = atoi(load_str);
    // User input (tainted data from source) - this can be 0!
    
    //SINK
    int load_per_core = total_load / cpu_cores;
    
    char result_buffer[256];
    snprintf(result_buffer, sizeof(result_buffer), 
             "CPU load distribution completed: %d load/core for %d cores", 
             load_per_core, cpu_cores);
    
    return std::string(result_buffer);
}

int processResourceOperations(const std::string& resource_data) {
    // Set resource message from source data for use in sinks
    set_resource_message(resource_data);
    
    int final_value = std::stoi(resource_data);
    
    // Pass numerical values from transformers to sinks (tainted data from source)
    std::string first_status = executeResourceCalculation(final_value);
    std::string second_status = executeUsageComputation(final_value);
    
    std::cout << "Resource operations completed: " << first_status << ", " << second_status << std::endl;
    
    return 0;
}

} // namespace resourceMonitorEngine
