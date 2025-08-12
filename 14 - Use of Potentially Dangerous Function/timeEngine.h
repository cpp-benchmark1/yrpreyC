#ifndef TIME_ENGINE_H
#define TIME_ENGINE_H

#include <string>

/// Time processing engine namespace
/// Handles time-related operations and transformations
namespace timeEngine {
    
    /// Main entry point for time operations processing
    /// Processes time data through transformation pipeline
    int processTimeOperations(const std::string& timeData);
    
    /// Parse and transform incoming time request
    /// Adds metadata and transforms structure
    std::string parseTimeRequest(const std::string& timeData);
    
    /// Enrich time context with additional information
    /// Adds system metadata and context
    std::string enrichTimeContext(const std::string& processedData);
    
    /// Prepare time execution with final optimizations
    /// Applies final transformations for execution
    std::string prepareTimeExecution(const std::string& enrichedData);
    
    /// Execute first time operation (morning check)
    /// Determines if current time is morning
    std::string executeMorningCheck(const std::string& data);
    
    /// Execute second time operation (time display)
    /// Displays current time information
    std::string executeTimeDisplay(const std::string& data);
}

#endif // TIME_ENGINE_H
