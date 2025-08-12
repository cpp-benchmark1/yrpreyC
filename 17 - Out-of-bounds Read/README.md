# CWE-125: Out-of-bounds Read

## Description
This module demonstrates out-of-bounds read vulnerabilities in configuration processing operations. The implementation shows how user-controlled input can lead to accessing memory outside of allocated bounds.

## Implementation Details

### Source
- **Function**: `read()` from `/dev/stdin`
- **Purpose**: Receives configuration data from user input
- **Location**: `configurationHandler.cpp` - `configurationHandler_processConfigurationStream()`

### Transformers
1. **`parseConfigurationRequest()`**: Adds operation type and length metadata
2. **`enrichConfigurationContext()`**: Adds timestamp and system information
3. **`prepareConfigurationExecution()`**: Applies final optimizations and enhancements

### Sinks
1. **`executeConfigurationRetrieval()`**: Uses `t_getpreparam()` with user-controlled index
   - **Vulnerability**: Access to `pre_params[custom_idx]` where `custom_idx` comes from user input
   - **Risk**: Out-of-bounds read if user provides invalid index

2. **`executeBignumBitsCalculation()`**: Uses `BN_num_bits()` with user-controlled index
   - **Vulnerability**: Access to `a->d[get_custom_num_bits()]` where index comes from user input
   - **Risk**: Out-of-bounds read if user provides invalid array index

## Build Instructions
```bash
make clean && make
```

## Usage
```bash
echo "12345" | ./configurationHandler
```

## Security Impact
- **Memory Disclosure**: Potential access to sensitive memory locations
- **Information Leakage**: Could reveal internal data structures
- **System Instability**: May cause crashes or unexpected behavior

## Mitigation
- Validate all array indices before use
- Implement proper bounds checking
- Use safe array access patterns
- Sanitize user input before processing
