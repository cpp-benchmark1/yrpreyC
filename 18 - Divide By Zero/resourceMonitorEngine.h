#ifndef RESOURCE_MONITOR_ENGINE_H
#define RESOURCE_MONITOR_ENGINE_H

#include <string>

/// Resource monitoring engine namespace
/// Handles resource monitoring operations and transformations
namespace resourceMonitorEngine {
    
    /// Main entry point for resource operations processing
    /// Processes resource data through transformation pipeline
    int processResourceOperations(const std::string& resource_data);
    
    /// Execute resource calculation operation
    /// Calculates resource usage using divide by zero vulnerable operations
    std::string executeResourceCalculation(int data);
    
    /// Execute usage computation operation
    /// Computes usage statistics using divide by zero vulnerable operations
    std::string executeUsageComputation(int data);
}

#endif // RESOURCE_MONITOR_ENGINE_H
