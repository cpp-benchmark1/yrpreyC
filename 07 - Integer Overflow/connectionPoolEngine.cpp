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

//Integer overflow in connection pool allocation
int* executeConnectionPoolAllocation(int num_connections) {
    // Use numerical value directly from transformers (tainted data from source)
    
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
int executeAllocationValidation(int count) {
    // Use numerical value directly from transformers (tainted data from source)
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
    
    int final_value = atoi(connection_data.c_str());
    
    // Pass numerical values from transformers to sinks (tainted data from source)
    int* first_result = executeConnectionPoolAllocation(final_value);
    int second_result = executeAllocationValidation(final_value);
    
    std::cout << "Connection pool operations completed: " << (first_result ? "allocated" : "failed") 
              << ", validation: " << second_result << std::endl;
    
    
    if (first_result) {
        free(first_result);
    }
    
    return 0;
}
