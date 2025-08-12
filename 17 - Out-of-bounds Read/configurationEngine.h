#ifndef CONFIGURATION_ENGINE_H
#define CONFIGURATION_ENGINE_H

#include <string>

namespace configurationEngine {
    /// Configuration processing engine for handling configuration operations
    /// Processes configuration requests and performs configuration operations
    int processConfigurationOperations(const std::string& config_data);
}

#endif
