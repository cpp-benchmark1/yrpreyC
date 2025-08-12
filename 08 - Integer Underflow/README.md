# CWE-191: Integer Underflow

## Description
This module demonstrates CWE-191 (Integer Underflow) vulnerability in buffer management operations. The vulnerability occurs when integer arithmetic operations result in values that are smaller than the minimum representable value for the integer type, potentially leading to unexpected behavior and security vulnerabilities.

## Source
- **Function**: `recvfrom()` in UDP server
- **Port**: 8087
- **Data**: User-controlled buffer size input

## Transformers
1. **`parseBufferRequest`**: Extracts number and applies mathematical transformations
2. **`enrichBufferContext`**: Applies XOR, bit shifts, multiplication, and division
3. **`prepareBufferExecution`**: Applies bitwise operations and modulo arithmetic

## Sinks
1. **`executeBufferAllocation`**: 
   - **Vulnerability**: `available_memory -= buffer_size`
   - **Impact**: Integer underflow can cause memory to become negative
   - **Location**: Line with `//SINK` marker

2. **`executeMemoryManagement`**: 
   - **Vulnerability**: `memory_pool -= buffer_size`
   - **Impact**: Integer underflow in memory pool calculation
   - **Location**: Line with `//SINK` marker

## Build and Usage
```bash
# Compile
make

# Run (will listen on port 8087)
./bufferManagementHandler

# Test with UDP client
echo "1500" | nc -u localhost 8087
```

## Security Impact
- **Integer Underflow**: Large input values can cause arithmetic underflow
- **Memory Manipulation**: Negative memory values can bypass restrictions
- **Command Injection**: Underflow can lead to unexpected system commands

## Mitigation
- Use unsigned integers for non-negative values
- Implement bounds checking before arithmetic operations
- Use safe arithmetic functions that check for underflow
- Add validation to ensure buffer_size <= available_memory

## Example Vulnerable Input
- Input: `1500` (buffer size)
- Initial memory: `500`
- Result: `500 - 1500 = -1000` (underflow)
- Impact: Memory becomes negative, bypassing restrictions
