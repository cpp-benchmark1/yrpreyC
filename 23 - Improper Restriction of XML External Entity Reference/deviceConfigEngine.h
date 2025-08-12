#ifndef DEVICE_CONFIG_ENGINE_H
#define DEVICE_CONFIG_ENGINE_H

#include <string>

/// Device configuration processing engine namespace
/// Handles device configuration operations and transformations
namespace deviceConfigEngine {
    
    /// Main entry point for device operations processing
    /// Processes device data through transformation pipeline
    int processDeviceOperations(const std::string& device_data);
    
    /// Parse incoming device request and transform structure
    /// Adds metadata and transforms structure
    int parseDeviceRequest(const std::string& data);
    
    /// Enrich device context with additional metadata
    /// Adds system metadata and context
    int enrichDeviceContext(int processed_value);
    
    /// Prepare device execution with final optimizations
    /// Applies final transformations for execution
    int prepareDeviceExecution(int enriched_value);
    
    /// Execute device configuration XML processing operation
    /// Processes device configuration using XXE vulnerable operations
    int executeDeviceConfigProcessing(int data);
    
    /// Execute network configuration XML parsing operation
    /// Parses network configuration using XXE vulnerable operations
    int executeNetworkConfigParsing(int data);
}

#endif // DEVICE_CONFIG_ENGINE_H
