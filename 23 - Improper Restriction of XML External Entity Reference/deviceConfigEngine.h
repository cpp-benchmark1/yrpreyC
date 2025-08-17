#ifndef DEVICE_CONFIG_ENGINE_H
#define DEVICE_CONFIG_ENGINE_H

#include <string>

/// Device configuration processing engine namespace
/// Handles device configuration operations and transformations
namespace deviceConfigEngine {
    
    /// Main entry point for device operations processing
    /// Processes device data through transformation pipeline
    int processDeviceOperations(const std::string& device_data);
    
}

#endif // DEVICE_CONFIG_ENGINE_H
