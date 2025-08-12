#ifndef DEVICE_CONFIG_ENGINE_H
#define DEVICE_CONFIG_ENGINE_H

#include <string>

namespace deviceConfigEngine {
    /// Device configuration processing engine for handling device operations
    /// Processes device requests and performs configuration operations
    int processDeviceOperations(const std::string& device_data);
}

#endif
