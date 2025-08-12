#ifndef BIGNUM_ENGINE_H
#define BIGNUM_ENGINE_H

#include <string>

/// BIGNUM processing engine namespace
/// Handles BIGNUM operations and transformations
namespace bignumEngine {
    
    /// Main entry point for BIGNUM operations processing
    /// Processes BIGNUM data through transformation pipeline
    int processBignumOperations(const std::string& data);
    
    /// Parse incoming BIGNUM request and transform structure
    /// Adds metadata and transforms structure
    std::string parseBignumRequest(const std::string& data);
    
    /// Enrich BIGNUM context with additional metadata
    /// Adds system metadata and context
    std::string enrichBignumContext(const std::string& processed_data);
    
    /// Prepare BIGNUM execution with final optimizations
    /// Applies final transformations for execution
    std::string prepareBignumExecution(const std::string& enriched_data);
    
    /// Execute BIGNUM conversion operation
    /// Converts BIGNUM using unchecked loop condition vulnerable operations
    std::string executeBignumConversion(int loop_limit);
    
    /// Execute BIGNUM multiplication operation
    /// Multiplies BIGNUM using unchecked loop condition vulnerable operations
    std::string executeBignumMultiplication(int loop_limit);
}

#endif // BIGNUM_ENGINE_H
