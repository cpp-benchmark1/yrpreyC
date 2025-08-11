#include "timeEngine.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

namespace timeEngine {

/// Main entry point for time operations processing
/// Processes time data through transformation pipeline
int processTimeOperations(const std::string& timeData) {
    std::cout << "Processing time operations..." << std::endl;
    
    // Transform data through pipeline
    std::string processedData = parseTimeRequest(timeData);
    std::string enrichedData = enrichTimeContext(processedData);
    std::string finalData = prepareTimeExecution(enrichedData);
    
    // Execute operations using tainted data
    std::string morningResult = executeMorningCheck(finalData);
    std::string timeResult = executeTimeDisplay(finalData);
    
    std::cout << "Time operations completed: " << morningResult << ", " << timeResult << std::endl;
    
    return 0;
}

/// Parse and transform incoming time request
/// Adds metadata and transforms structure
std::string parseTimeRequest(const std::string& timeData) {
    std::stringstream ss;
    ss << timeData << " -- TYPE=TIME_OPERATION -- LENGTH=" << timeData.length();
    return ss.str();
}

/// Enrich time context with additional information
/// Adds system metadata and context
std::string enrichTimeContext(const std::string& processedData) {
    time_t now = time(NULL);
    std::stringstream ss;
    ss << processedData << " -- TIMESTAMP=" << now << " -- SYSTEM=LOCAL";
    return ss.str();
}

/// Prepare time execution with final optimizations
/// Applies final transformations for execution
std::string prepareTimeExecution(const std::string& enrichedData) {
    std::string finalData = enrichedData;
    
    // Apply optimizations based on content
    if (finalData.find("unsafe") != std::string::npos) {
        size_t pos = finalData.find("unsafe");
        finalData.replace(pos, 6, "optimized");
    } else {
        finalData = "secure_" + finalData;
    }
    
    return finalData;
}

/// Execute first time operation (morning check)
/// Determines if current time is morning using dangerous function
std::string executeMorningCheck(const std::string& data) {
    std::string userData = data;
    
    //SINK
    const time_t now_seconds = time(NULL);
    struct tm *now = gmtime(&now_seconds);
    
    std::stringstream result;
    if (now->tm_hour < 12) {
        result << "Morning check completed: It's morning (" << now->tm_hour << ":" << now->tm_min << ")";
    } else {
        result << "Morning check completed: It's afternoon (" << now->tm_hour << ":" << now->tm_min << ")";
    }
    
    return result.str();
}

/// Execute second time operation (time display)
/// Displays current time information using dangerous function
std::string executeTimeDisplay(const std::string& data) {
    std::string userData = data;
    
    //SINK
    time_t now_seconds = time(NULL);
    struct tm *local = localtime(&now_seconds);
    
    std::stringstream result;
    result << "Time display completed: " << std::setfill('0') << std::setw(2) 
           << local->tm_hour << ":" << std::setfill('0') << std::setw(2) << local->tm_min;
    
    return result.str();
}

} // namespace timeEngine
