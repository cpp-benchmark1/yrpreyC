# CWE-190: Integer Overflow

## Description
This module demonstrates CWE-190 (Integer Overflow) vulnerability in connection pool management operations. The vulnerability occurs when integer arithmetic operations result in values that exceed the maximum representable value for the integer type, potentially leading to memory allocation issues and security vulnerabilities.

## Source
- **Function**: `recvfrom()` in UDP server
- **Port**: 8086
- **Data**: User-controlled connection count input

## Transformers
1. **`parseConnectionRequest`**: Adds operation type and length metadata
2. **`enrichConnectionContext`**: Adds timestamp and system information
3. **`prepareConnectionExecution`**: Applies final formatting optimizations

## Sinks
1. **`executeConnectionPoolAllocation`**: 
   - **Vulnerability**: `int alloc_size = num_connections * sizeof(int)`
   - **Impact**: Integer overflow can cause incorrect memory allocation
   - **Location**: Line with `//SINK` marker

2. **`executeAllocationValidation`**: 
   - **Vulnerability**: `int alloc_size = count * element_size`
   - **Impact**: Integer overflow in validation logic
   - **Location**: Line with `//SINK` marker

## Build and Usage
```bash
# Compile
make

# Run (will listen on port 8086)
./connectionPoolHandler

# Test with UDP client
echo "2147483647" | nc -u localhost 8086
```

## Security Impact
- **Integer Overflow**: Large input values can cause arithmetic overflow
- **Memory Allocation**: Incorrect allocation sizes may lead to buffer overflows
- **Validation Bypass**: Overflow can bypass size checks

## Mitigation
- Use `std::multiply` or similar safe arithmetic functions
- Implement bounds checking before arithmetic operations
- Use larger integer types (e.g., `size_t`, `uint64_t`) for size calculations
- Add overflow detection and handling

## Example Vulnerable Input
- Input: `2147483647` (MAX_INT)
- Result: `2147483647 * 4 = -4` (overflow)
- Allocation: Attempts to allocate -4 bytes
