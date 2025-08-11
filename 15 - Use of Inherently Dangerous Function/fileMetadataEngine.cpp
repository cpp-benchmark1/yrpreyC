#include "fileMetadataEngine.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <ctime>

namespace fileMetadataEngine {

/// Main entry point for file metadata processing
/// Processes metadata through transformation pipeline
int processFileMetadata(const std::string& metadataPackage) {
    std::cout << "Processing file metadata operations..." << std::endl;
    
    // Transform data through pipeline
    std::string processedData = parseMetadataRequest(metadataPackage);
    std::string enrichedData = enrichMetadataContext(processedData);
    std::string finalData = prepareMetadataExecution(enrichedData);
    
    // Execute operations using tainted data
    std::string titleResult = executeTitleProcessing(finalData);
    std::string categoryResult = executeCategoryProcessing(finalData);
    
    std::cout << "Metadata operations completed: " << titleResult << ", " << categoryResult << std::endl;
    
    return 0;
}

/// Parse and transform incoming metadata request
/// Adds metadata and transforms structure
std::string parseMetadataRequest(const std::string& metadataPackage) {
    std::stringstream ss;
    ss << metadataPackage << " -- TYPE=FILE_METADATA_OPERATION -- LENGTH=" << metadataPackage.length();
    return ss.str();
}

/// Enrich metadata context with additional information
/// Adds system metadata and context
std::string enrichMetadataContext(const std::string& processedData) {
    std::stringstream ss;
    ss << processedData << " -- TIMESTAMP=" << time(NULL) << " -- SYSTEM=FILE_PROCESSOR";
    return ss.str();
}

/// Prepare metadata execution with final optimizations
/// Applies final transformations for execution
std::string prepareMetadataExecution(const std::string& enrichedData) {
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

/// Execute first metadata operation (filename processing)
/// Processes filename using dangerous function gets() with tainted data
std::string executeTitleProcessing(const std::string& data) {
    std::string userData = data;
    
    // Extract filename from tainted data (simulating parsing)
    std::string filename = userData.substr(0, 50); // Use tainted data
    
    char filename_buffer[128];
    strcpy(filename_buffer, filename.c_str()); // Copy tainted data
    
    //SINK
    gets(filename_buffer); 
    
    std::stringstream result;
    result << "Filename processing completed: '" << filename_buffer << "' (length: " << strlen(filename_buffer) << " bytes)";
    
    return result.str();
}

/// Execute second metadata operation (category processing)
/// Processes file category using dangerous function gets() with tainted data
std::string executeCategoryProcessing(const std::string& data) {
    std::string userData = data;
    
    // Extract category from tainted data (simulating parsing)
    std::string category = userData.substr(50, 50); // Use tainted data
    
    char category_buffer[128];
    strcpy(category_buffer, category.c_str()); // Copy tainted data
    
    //SINK
    gets(category_buffer); 
    
    std::stringstream result;
    result << "Category processing completed: '" << category_buffer << "' (length: " << strlen(category_buffer) << " bytes)";
    
    return result.str();
}

} // namespace fileMetadataEngine
