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

// Transformers
/// Parse incoming buffer request and transform structure
int parseBufferRequest(const std::string& buffer_data) {
    // Extract first number from string input
    int base_value = atoi(buffer_data.c_str());
    // Apply mathematical transformation
    int transformed_value = base_value * 3 + 200;
    // Additional mathematical operations
    int hash_value = transformed_value ^ 0xBADCAFE;
    int shifted_value = hash_value << 4;
    int rotated_value = (shifted_value >> 2) | (shifted_value << 30);
    int final_result = rotated_value % 0x7FFFFFFF;
    return final_result;
}

/// Enrich buffer context with additional metadata
int enrichBufferContext(int processed_value) {
    // Apply mathematical operations
    int enriched_value = processed_value ^ 0xDEADBEEF;
    enriched_value = enriched_value << 3;
    // Complex mathematical transformations
    int xor_result = enriched_value ^ 0x87654321;
    int bit_shift = xor_result >> 5;
    int multiplication = bit_shift * 11;
    int division = multiplication / 5;
    int remainder = division % 0xFFFF;
    return remainder;
}

/// Prepare buffer execution with final optimizations
int prepareBufferExecution(int enriched_value) {
    // Final mathematical transformation
    int final_value = enriched_value % 1000000;
    final_value = final_value + 1000;
    // Advanced mathematical processing
    int bitwise_and = final_value & 0x00FF00FF;
    int bitwise_or = bitwise_and | 0xFF00FF00;
    int left_shift = bitwise_or << 3;
    int right_shift = left_shift >> 4;
    int modulo_result = right_shift % 0x2000000;
    return modulo_result;
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
    
    // Transform the received data through transformers (returning numerical values)
    int processed_value = parseBufferRequest(buffer_data);
    int enriched_value = enrichBufferContext(processed_value);
    int final_value = prepareBufferExecution(enriched_value);
    
    // Pass numerical values from transformers to sinks (tainted data from source)
    bool first_result = executeBufferAllocation(final_value);
    executeMemoryManagement(final_value);
    
    std::cout << "Buffer management operations completed: " << (first_result ? "success" : "failed") << std::endl;
    std::cout << "Transformer values: " << processed_value << " -> " << enriched_value << " -> " << final_value << std::endl;
    
    return 0;
}
