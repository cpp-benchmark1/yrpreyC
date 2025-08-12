#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "configurationEngine.h"


// Internal functions
std::string parseConfigurationRequest(const std::string& data);
std::string enrichConfigurationContext(const std::string& data);
std::string prepareConfigurationExecution(const std::string& data);
std::string executeConfigurationRetrieval(const std::string& data);
std::string executeBignumBitsCalculation(const std::string& data);

// Configuration functions
struct t_preconf* t_getpreparam(int config_index);
int t_getprecount(void);
struct t_confent* gettcid(int config_id);

// Global variable to store TCP server message from source
std::string g_tcp_message;

// Function to set TCP message from source
void set_tcp_message(const std::string& message) {
    g_tcp_message = message;
}

// Function to get TCP server message (tainted from user input)
const char* tcp_server_msg() {
    return g_tcp_message.c_str();
}

// Function to get UDP server message (tainted from user input)
const char* udp_server_msg() {
    return g_tcp_message.c_str();
}


// Configuration structures
struct pre_struct {
    int state;
    struct {
        struct {
            char* data;
        } modulus;
        struct {
            char* data;
        } generator;
    } preconf;
    char* modbuf;
    char* genbuf;
};

struct t_preconf {
    int modulus;
    int generator;
};

struct t_confent {
    int index;
    int modulus;
    int generator;
};

// BIGNUM structures and constants
typedef unsigned long BN_ULONG;
#define BN_BITS2 32
#define BN_BYTES 4

struct BIGNUM {
    BN_ULONG *d;
    int top;
    int dmax;
    int neg;
    int flags;
};

// Global configuration parameters
static struct pre_struct pre_params[100];
static char modbuf_data[100][256];
static char genbuf_data[100][256];


std::string parseConfigurationRequest(const std::string& data) {
    std::string processed_data = data;
    processed_data += " -- TYPE=CONFIG_OPERATION -- LENGTH=" + std::to_string(data.length());
    return processed_data;
}

std::string enrichConfigurationContext(const std::string& data) {
    std::string enriched_data = data;
    enriched_data += " -- TIMESTAMP=" + std::to_string(time(NULL)) + " -- SYSTEM=LOCAL";
    return enriched_data;
}

std::string prepareConfigurationExecution(const std::string& data) {
    std::string final_data = data;
    if (final_data.find("config") != std::string::npos) {
        final_data = "enhanced_" + final_data;
    } else {
        final_data = "standard_" + final_data;
    }
    return final_data;
}


// Initialize configuration parameters
void init_config_params() {
    for (int i = 0; i < 100; i++) {
        pre_params[i].state = 1;
        pre_params[i].modbuf = modbuf_data[i];
        pre_params[i].genbuf = genbuf_data[i];
        strcpy(pre_params[i].modbuf, "default_modulus");
        strcpy(pre_params[i].genbuf, "default_generator");
    }
}

// Get parameter count
int t_getprecount() {
    return (sizeof(pre_params) / sizeof(struct pre_struct));
}

// Get configuration by ID
struct t_confent* gettcid(int config_id) {
    struct t_preconf *tcp;
    
    if (config_id <= 0 || config_id > t_getprecount()) {
        return NULL;
    }
    
    tcp = t_getpreparam(config_id - 1);
    static struct t_confent sysconf;
    sysconf.index = config_id;
    if (tcp) {
        sysconf.modulus = tcp->modulus;
        sysconf.generator = tcp->generator;
    }
    
    return &sysconf;
}

// Get parameter by index
struct t_preconf* t_getpreparam(int config_index) {
    int param_offset;
    if (config_index > 0) {
        const char* custom_idx_str = tcp_server_msg();
        param_offset = atoi(custom_idx_str);
    } else {
        param_offset = config_index;
    }
    
    if (pre_params[config_index].state == 0) {
        // Wire up storage
        //SINK
        pre_params[config_index].preconf.modulus.data = pre_params[param_offset].modbuf;
        pre_params[config_index].preconf.generator.data = pre_params[config_index].genbuf;
    }
    
    static struct t_preconf result;
    result.modulus = 12345;
    result.generator = 67890;
    return &result;
}

std::string executeConfigurationRetrieval(const std::string& data) {
    std::string userData = data;
    
    // Initialize configuration parameters
    init_config_params();
    
    // Extract index from user data (tainted data from source)
    std::string index_str = userData.substr(0, 10);
    int config_index = atoi(index_str.c_str());
    
    // This will cause out-of-bounds read if config_index is manipulated by user input
    struct t_confent* result = gettcid(config_index);
    
    if (result) {
        return "Configuration retrieved successfully for index: " + std::to_string(result->index);
    } else {
        return "Configuration retrieval failed for index: " + std::to_string(config_index);
    }
}


// Get BIGNUM limit
int get_bn_limit() {
    const char* bn_limit_str = udp_server_msg();
    int bn_limit = atoi(bn_limit_str);
    return bn_limit;
}

// Get custom number of bits
int get_custom_num_bits() {
    const char* num_bits_str = tcp_server_msg();
    int num_bits = atoi(num_bits_str);
    return num_bits;
}

// Calculate number of bits in BIGNUM
int BN_num_bits(const BIGNUM *a) {
    BN_ULONG l;
    int i;
    
    if (a->top == 0) return(0);
    
    //SINK
    l = a->d[get_custom_num_bits()];
    
    i = (a->top-1) * BN_BITS2;
    return(i + 8 + (int)l); // Use l to avoid unused variable warning
}

std::string executeBignumBitsCalculation(const std::string& data) {
    std::string userData = data;
    
    // Create a BIGNUM structure
    BIGNUM bn;
    BN_ULONG d_array[100];
    bn.d = d_array;
    bn.top = 50;
    bn.dmax = 100;
    bn.neg = 0;
    bn.flags = 0;
    
    // Initialize d array
    for (int i = 0; i < 100; i++) {
        d_array[i] = i + 1;
    }
    
    // This will cause out-of-bounds read if get_custom_num_bits() returns invalid index
    int bits = BN_num_bits(&bn);
    
    return "BIGNUM bits calculation completed: " + std::to_string(bits) + " bits";
}




int configurationEngine::processConfigurationOperations(const std::string& config_data) {
    // Set TCP message from source data for use in sinks
    set_tcp_message(config_data);
    
    // Transform the received data through transformers
    std::string processed_data = parseConfigurationRequest(config_data);
    std::string enriched_data = enrichConfigurationContext(processed_data);
    std::string final_data = prepareConfigurationExecution(enriched_data);
    
    // Use the data in sinks that demonstrate out-of-bounds read
    std::string first_status = executeConfigurationRetrieval(final_data);
    std::string second_status = executeBignumBitsCalculation(final_data);
    
    std::cout << "Configuration operations completed: " << first_status << ", " << second_status << std::endl;
    
    return 0;
}
