#ifndef SERVER_CONFIGURATION_ENGINE_H
#define SERVER_CONFIGURATION_ENGINE_H

#include <string>

namespace serverConfigurationEngine {
    /// Server configuration processing engine for handling configuration operations
    /// Processes configuration requests and performs configuration operations
    int processConfigurationOperations(const std::string& config_data);
}

#endif
