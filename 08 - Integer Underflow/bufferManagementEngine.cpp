#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdio>

// Global message storage for source data
std::string g_buffer_message;

// Function to set buffer message (tainted from user input)
void set_buffer_message(const std::string& message) {
    g_buffer_message = message;
}

// Function to get buffer message (tainted from user input)
const char* buffer_server_msg() {
    return g_buffer_message.c_str();
}


//Integer underflow in buffer allocation
bool executeBufferAllocation(int buffer_size) {
    int available_memory = 1000; // Initial memory
    
    // Integer underflow if buffer_size > available_memory
    //SINK
    available_memory -= buffer_size; 
    
    std::cout << "Buffer allocation completed: " << available_memory << " remaining" << std::endl;
    
    return (available_memory > 0);
}

//Integer underflow in memory management
void executeMemoryManagement(int buffer_size) {
    int memory_pool = 500; // Initial memory pool
    
    // Integer underflow if buffer_size > memory_pool
    // Vulnerable: no check for underflow
    //SINK
    memory_pool -= buffer_size;
    
    // Logic based on remaining memory
    if (memory_pool > 0) {
        // Making this exploitable (HTTP request using the tainted value)
        char cmd[200];
        snprintf(cmd, sizeof(cmd), "curl http://localhost:9999/setmemory?memory=%d", memory_pool);
        system(cmd);
        std::cout << "Memory management updated: " << memory_pool << " remaining" << std::endl;
    } else {
        std::cout << "Memory exhausted." << std::endl;
    }
}

int bufferManagementEngine_processBufferManagementOperations(const std::string& buffer_data) {
    // Set buffer message from source data for use in sinks
    set_buffer_message(buffer_data);
    
    int final_value = atoi(buffer_data.c_str());
    
    // Pass numerical values from transformers to sinks (tainted data from source)
    bool first_result = executeBufferAllocation(final_value);
    executeMemoryManagement(final_value); 
    
    std::cout << "Buffer management operations completed: " << (first_result ? "success" : "failed") << std::endl;
   
    return 0;
}
