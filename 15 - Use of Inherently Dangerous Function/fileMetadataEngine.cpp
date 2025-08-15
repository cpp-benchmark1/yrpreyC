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
    
    char file_directory[128];

    
    //SINK
    gets(file_directory); 
    std::string full_path = filename + std::string(file_directory);


    
    return full_path;
}

/// Execute second metadata operation (category processing)
/// Processes file category using dangerous function gets() with tainted data
std::string executeCategoryProcessing(const std::string& data) {
    std::string userData = data;
    
    // Extract category from tainted data (simulating parsing)
    std::string category = userData.substr(50, 50); // Use tainted data
    
    char category_buffer[128];

    
    //SINK
    gets(category_buffer); 
    std::string final_category = category + std::string(category_buffer);
    std::stringstream result;
    result << "Category processing completed: '" << final_category << "' (length: " << final_category.size() << " bytes)";
    
    return result.str();
}

} // namespace fileMetadataEngine
