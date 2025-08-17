#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "networkEngine.h"

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

//Response cloning with NULL pointer dereference
int executeResponseCloning(int data) {
    // Use numerical data directly from source (tainted data from source)
    int bucket_size = data;
    
    // Bucket allocation function that can return NULL
    int* bucket_size_ptr = &bucket_size;
    bucket_size_ptr = nullptr;
    
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
    int ip_value = data;

    // Bucket allocation function that can return NULL
    int* host_name_ptr = &ip_value;
    host_name_ptr = nullptr;

    
    // This will cause NULL pointer dereference if hp is NULL
    //SINK
    if (*host_name_ptr > 1) {
        char result_buffer[256];
        snprintf(result_buffer, sizeof(result_buffer), 
                 "Host lookup completed: %d", 
                 ip_value);
        return 0;    
    } else {
        return 1;
    }
    
}

int networkEngine::processNetworkOperations(const std::string& network_data) {
    // Set network message from source data for use in sinks
    set_network_message(network_data);
    
    int final_value = atoi(network_data.c_str());

    // Pass numerical values directly to sinks
    int first_status = executeResponseCloning(final_value);
    int second_status = executeHostLookup(final_value);
    
    std::cout << "Network operations completed: " << first_status << ", " << second_status << std::endl;
    
    return 0;
}
