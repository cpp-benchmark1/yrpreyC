#ifndef BIGNUM_ENGINE_H
#define BIGNUM_ENGINE_H

#include <string>

/// BIGNUM processing engine namespace
/// Handles BIGNUM operations and transformations
namespace bignumEngine {
    
    /// Main entry point for BIGNUM operations processing
    /// Processes BIGNUM data through transformation pipeline
    int processBignumOperations(const std::string& data);
    
    /// Execute BIGNUM conversion operation
    /// Converts BIGNUM using unchecked loop condition vulnerable operations
    std::string executeBignumConversion(int loop_limit);
    
    /// Execute BIGNUM multiplication operation
    /// Multiplies BIGNUM using unchecked loop condition vulnerable operations
    std::string executeBignumMultiplication(int loop_limit);
}

#endif // BIGNUM_ENGINE_H
