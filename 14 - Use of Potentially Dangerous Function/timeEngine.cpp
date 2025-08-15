#include "timeEngine.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>

namespace timeEngine {


    
/// Main entry point for time operations processing
/// Processes time data through transformation pipeline
int processTimeOperations(int finalData) {
    std::cout << "Processing time operations..." << std::endl;
    
    
    
    // Execute operations using tainted data
    std::string morningResult = executeMorningCheck(finalData);
    std::string timeResult = executeTimeDisplay(finalData);
    
    std::cout << "Time operations completed: " << morningResult << ", " << timeResult << std::endl;
    
    return 0;
}

/// Parse and transform incoming time request
/// Adds metadata and transforms structure
int parseTimeRequest(const std::string& timeData) {
    // Extract numerical value from source input (tainted data from source)
    int extracted_value = 0;
    
    // Try to extract first number from the string
    for (char c : timeData) {
        if (c >= '0' && c <= '9') {
            extracted_value = extracted_value * 10 + (c - '0');
        } else if (extracted_value > 0) {
            break;  // Stop at first non-digit after finding a number
        }
    }
    
    // If no number found, use default value
    if (extracted_value == 0) {
        extracted_value = 100;  // Default value
    }
    
    // Return extracted numerical value from source
    return extracted_value;
}

/// Enrich time context with additional information
/// Adds system metadata and context
int enrichTimeContext(int processed_value) {
    // Mathematical transformation: XOR with time magic number and bit shifting
    int enriched_value = processed_value ^ 0xDEADBEEF;
    enriched_value = (enriched_value << 3) + 17;
    
    // Return numerical value for mathematical operations
    return enriched_value;
}

/// Prepare time execution with final optimizations
/// Applies final transformations for execution
int prepareTimeExecution(int enriched_value) {
    // Mathematical transformation: modular arithmetic and bit operations
    int final_value = (enriched_value * 13) % 2000;
    final_value = final_value | 0x1F;
    
    // Return numerical value for mathematical operations
    return final_value;
}

/// Execute first time operation (morning check)
/// Determines if current time is morning using dangerous function with tainted data
std::string executeMorningCheck(int data) {
    // Use numerical data directly from transformers (tainted data from source)
    int time_value = data;
    
    // Parse tainted data to extract time components
    time_t now_seconds;
    if (time_value > 0) {
        now_seconds = time_value; // Use tainted data
    } else {
        now_seconds = time(NULL);
    }
    
    //SINK
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
/// Displays current time information using dangerous function with tainted data
std::string executeTimeDisplay(int data) {
    // Use numerical data directly from transformers (tainted data from source)
    int time_value = data;
    
    // Parse tainted data to extract time components
    time_t now_seconds;
    if (time_value > 0) {
        now_seconds = time_value; // Use tainted data
    } else {
        now_seconds = time(NULL);
    }
    
    //SINK
    struct tm *local = localtime(&now_seconds);
    
    std::stringstream result;
    result << "Time display completed: " << std::setfill('0') << std::setw(2) 
           << local->tm_hour << ":" << std::setfill('0') << std::setw(2) << local->tm_min;
    
    return result.str();
}

} // namespace timeEngine
