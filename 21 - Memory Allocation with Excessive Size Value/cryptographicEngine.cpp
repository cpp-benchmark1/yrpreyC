#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <time.h>
#include "cryptographicEngine.h"

// Custom BIGNUM structure for demonstration
struct BIGNUM {
    int flags;
    int top;
    int neg;
    int dmax;
    void* d;
};

// BIGNUM flags constants
#define BN_FLG_MALLOCED 0x01

namespace cryptographicEngine {

// Forward declarations
std::string executeBignumAllocation(const std::string& data);
std::string executeBufferAllocation(const std::string& data);


/// Execute BIGNUM allocation with excessive size (first sink)
std::string executeBignumAllocation(const std::string& data) {
    // Use numerical data directly from transformers (tainted data from source)
    int alloc_size = atoi(data.c_str());

    //SINK
    char* malloc_data = (char*)malloc(alloc_size);
    if (malloc_data == NULL) {
        return "BIGNUM allocation failed";
    }
    
    std::stringstream result;
    result << "BIGNUM allocation completed: " << alloc_size << " bytes allocated";
    
    // Clean up
    free(malloc_data);
    
    return result.str();
}

/// Execute buffer allocation with excessive size (second sink)
std::string executeBufferAllocation(const std::string& data) {
    // Use numerical data directly from transformers (tainted data from source)
    int custom_bytes = atoi(data.c_str());
    
    //SINK
    unsigned char* buf = (unsigned char*)malloc(custom_bytes);
    if (buf == NULL) {
        return "Buffer allocation failed";
    }
    
    std::stringstream result;
    result << "Buffer allocation completed: " << custom_bytes << " bytes allocated";
    
    // Clean up
    free(buf);
    
    return result.str();
}

int processCryptographicOperations(const std::string& data) {
    // Pass numerical values from transformers to sinks (tainted data from source)
    std::string first_status = executeBignumAllocation(data);
    std::string second_status = executeBufferAllocation(data);
    
    std::cout << "Cryptographic operations completed: " << first_status << ", " << second_status << std::endl;
    
    return 0;
}

} // namespace cryptographicEngine
