#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdio>

// Global message storage for source data
std::string g_connection_message;

// Function to set connection message (tainted from user input)
void set_connection_message(const std::string& message) {
    g_connection_message = message;
}

// Function to get connection message (tainted from user input)
const char* connection_server_msg() {
    return g_connection_message.c_str();
}

// Transformers
/// Parse incoming connection request and transform structure
int parseConnectionRequest(const std::string& connection_data) {
    // Extract first number from string input
    int base_value = atoi(connection_data.c_str());
    // Apply mathematical transformation
    int transformed_value = base_value * 2 + 100;
    // Additional mathematical operations
    int hash_value = transformed_value ^ 0xCAFEBABE;
    int shifted_value = hash_value << 3;
    int rotated_value = (shifted_value >> 1) | (shifted_value << 31);
    int final_result = rotated_value % 0x7FFFFFFF;
    return final_result;
}

/// Enrich connection context with additional metadata
int enrichConnectionContext(int processed_value) {
    // Apply mathematical operations
    int enriched_value = processed_value ^ 0xDEADBEEF;
    enriched_value = enriched_value << 2;
    // Complex mathematical transformations
    int xor_result = enriched_value ^ 0x12345678;
    int bit_shift = xor_result >> 4;
    int multiplication = bit_shift * 7;
    int division = multiplication / 3;
    int remainder = division % 0xFFFF;
    return remainder;
}

/// Prepare connection execution with final optimizations
int prepareConnectionExecution(int enriched_value) {
    // Final mathematical transformation
    int final_value = enriched_value % 1000000;
    final_value = final_value + 500;
    // Advanced mathematical processing
    int bitwise_and = final_value & 0x00FF00FF;
    int bitwise_or = bitwise_and | 0xFF00FF00;
    int left_shift = bitwise_or << 1;
    int right_shift = left_shift >> 2;
    int modulo_result = right_shift % 0x1000000;
    return modulo_result;
}

//Integer overflow in connection pool allocation
int* executeConnectionPoolAllocation(const std::string& data) {
    // Extract numerical value from source data (tainted data from source)
    int num_connections = atoi(data.c_str());
    
    //SINK
    int alloc_size = num_connections * sizeof(int);
    
    if (alloc_size < 8192) {
        int *connection_slots = (int *)malloc(alloc_size);
        if (!connection_slots) {
            std::cout << "Failed to allocate resources for connections." << std::endl;
            return NULL;
        }
        
        for (int i = 0; i < num_connections; i++) {
            connection_slots[i] = i;
        }
        
        std::cout << "Connection pool allocation completed: " << num_connections << " connections" << std::endl;
        
        return connection_slots;
    }
    
    return NULL;
}

//Integer overflow in allocation size validation
int executeAllocationValidation(const std::string& data) {
    // Extract numerical value from source data (tainted data from source)
    int count = atoi(data.c_str());
    int element_size = sizeof(int);
    
    //SINK
    int alloc_size = count * element_size;
    
    // Naive check (same logic as before)
    int is_safe = alloc_size < 8192;
    
    std::cout << "Allocation validation completed: " << (is_safe ? "safe" : "unsafe") << std::endl;
    
    return is_safe;
}

int connectionPoolEngine_processConnectionPoolOperations(const std::string& connection_data) {
    // Set connection message from source data for use in sinks
    set_connection_message(connection_data);
    
    // Transform the received data through transformers (returning numerical values)
    int processed_value = parseConnectionRequest(connection_data);
    int enriched_value = enrichConnectionContext(processed_value);
    int final_value = prepareConnectionExecution(enriched_value);
    
    // Pass source data directly to sinks (tainted data from source)
    int* first_result = executeConnectionPoolAllocation(connection_data);
    int second_result = executeAllocationValidation(connection_data);
    
    std::cout << "Connection pool operations completed: " << (first_result ? "allocated" : "failed") 
              << ", validation: " << second_result << std::endl;
    
    std::cout << "Transformer values: " << processed_value << " -> " << enriched_value << " -> " << final_value << std::endl;
    
    if (first_result) {
        free(first_result);
    }
    
    return 0;
}
