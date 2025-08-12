#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "networkEngine.h"

// Forward declarations for internal functions
int parseNetworkRequest(const std::string& data);
int enrichNetworkContext(int processed_value);
int prepareNetworkExecution(int enriched_value);
int executeResponseCloning(int data);
int executeHostLookup(int data);

// Global variable to store network data from source
std::string g_network_message;

// Function to set network message from source
void set_network_message(const std::string& message) {
    g_network_message = message;
}

// Function to get network message (tainted from user input)
const char* network_server_msg() {
    return g_network_message.c_str();
}

// Transformers
int parseNetworkRequest(const std::string& data) {
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

int enrichNetworkContext(int processed_value) {
    // Mathematical transformation: XOR with network magic number and bit shifting
    int enriched_value = processed_value ^ 0xCAFEBABE;
    enriched_value = (enriched_value << 3) + 7;
    
    // Return numerical value for mathematical operations
    return enriched_value;
}

int prepareNetworkExecution(int enriched_value) {
    // Mathematical transformation: modular arithmetic and bit operations
    int final_value = (enriched_value * 11) % 2000;
    final_value = final_value | 0x1F;
    
    // Return numerical value for mathematical operations
    return final_value;
}

//Response cloning with NULL pointer dereference
int executeResponseCloning(int data) {
    // Use numerical data directly from source (tainted data from source)
    int bucket_size = data;
    
    // Bucket allocation function that can return NULL
    int* bucket_size_ptr = nullptr;
    if (bucket_size > 0 && bucket_size < 1000) {
        bucket_size_ptr = &bucket_size;
    }
    
    // Source bucket structure
    struct ap_bucket_response {
        int status;
        char* reason;
        void* headers;
        void* notes;
    };
    
    struct ap_bucket {
        void* data;
        void* free;
        void* list;
        void* type;
    };
    
    // Create source bucket
    ap_bucket_response sresp;
    sresp.status = 200;
    sresp.reason = "OK";
    sresp.headers = nullptr;
    sresp.notes = nullptr;
    
    ap_bucket source;
    source.data = &sresp;

    // This will cause NULL pointer dereference if bucket_size_ptr is NULL    
    //SINK
    int allocated_size = *bucket_size_ptr;
    
    char result_buffer[256];
    snprintf(result_buffer, sizeof(result_buffer), 
             "Response cloning completed: allocated %d bytes", 
             allocated_size);
    
    return allocated_size;  // Return int instead of string
}

//Host lookup with NULL pointer dereference
int executeHostLookup(int data) {
    // Use numerical data directly from source (tainted data from source)
    int ip_value = data;
    
    // Host lookup that can return NULL
    struct hostent* hp = nullptr;
    
    // IP address validation based on numerical value
    if (ip_value > 0 && ip_value < 1000) {
        // Valid IP range, but host lookup might still return NULL
        if (ip_value == 0 || ip_value > 999) {
            hp = nullptr;  // Failed lookup
        } else {
            // Successful lookup
            static struct hostent mock_host;
            static char hostname[] = "example.com";
            mock_host.h_name = hostname;
            hp = &mock_host;
        }
    }
    
    char hostname[64];

    
    // This will cause NULL pointer dereference if hp is NULL
    //SINK
    strcpy(hostname, hp->h_name);
    
    char result_buffer[256];
    snprintf(result_buffer, sizeof(result_buffer), 
             "Host lookup completed: %d -> %s", 
             ip_value, hostname);
    
    return 0;  // Return int instead of string
}

int networkEngine::processNetworkOperations(const std::string& network_data) {
    // Set network message from source data for use in sinks
    set_network_message(network_data);
    
    // Transform the received data through transformers (returning numerical values)
    int processed_value = parseNetworkRequest(network_data);
    int enriched_value = enrichNetworkContext(processed_value);
    int final_value = prepareNetworkExecution(enriched_value);
    
    // Pass numerical values directly to sinks
    int first_status = executeResponseCloning(final_value);
    int second_status = executeHostLookup(final_value);
    
    std::cout << "Network operations completed: " << first_status << ", " << second_status << std::endl;
    
    return 0;
}
