#ifndef RESOURCE_MONITOR_ENGINE_H
#define RESOURCE_MONITOR_ENGINE_H

#include <string>

namespace resourceMonitorEngine {
    /// Resource monitoring processing engine for handling resource operations
    /// Processes resource requests and performs monitoring operations
    int processResourceOperations(const std::string& resource_data);
}

#endif
