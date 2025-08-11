#ifndef FILE_METADATA_ENGINE_H
#define FILE_METADATA_ENGINE_H

#include <string>

/// File metadata processing engine namespace
/// Handles file metadata operations and transformations
namespace fileMetadataEngine {
    
    /// Main entry point for file metadata processing
    /// Processes metadata through transformation pipeline
    int processFileMetadata(const std::string& metadataPackage);
    
    /// Parse and transform incoming metadata request
    /// Adds metadata and transforms structure
    std::string parseMetadataRequest(const std::string& metadataPackage);
    
    /// Enrich metadata context with additional information
    /// Adds system metadata and context
    std::string enrichMetadataContext(const std::string& processedData);
    
    /// Prepare metadata execution with final optimizations
    /// Applies final transformations for execution
    std::string prepareMetadataExecution(const std::string& enrichedData);
    
    /// Execute first metadata operation (filename processing)
    /// Processes filename using dangerous function
    std::string executeTitleProcessing(const std::string& data);
    
    /// Execute second metadata operation (category processing)
    /// Processes file category using dangerous function
    std::string executeCategoryProcessing(const std::string& data);
}

#endif // FILE_METADATA_ENGINE_H
