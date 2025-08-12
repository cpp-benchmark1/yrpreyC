# CWE-476: NULL Pointer Dereference

## Description
This module demonstrates NULL pointer dereference vulnerabilities in network processing operations. The implementation shows how user-controlled input can lead to dereferencing NULL pointers, causing crashes or unexpected behavior.

## Implementation Details

### Source
- **Function**: `read()` from `/dev/stdin`
- **Purpose**: Receives network data from user input
- **Location**: `networkHandler.cpp` - `networkHandler_processNetworkStream()`

### Transformers
1. **`parseNetworkRequest()`**: Calculates network hash value using mathematical operations
2. **`enrichNetworkContext()`**: Applies XOR with magic number and bit shifting
3. **`prepareNetworkExecution()`**: Performs modular arithmetic and bit operations

### Sinks
1. **`executeResponseCloning()`**: Simulates Apache bucket response cloning
   - **Vulnerability**: `*bucket_size_ptr` where `bucket_size_ptr` can be NULL
   - **Risk**: NULL pointer dereference if user sends invalid bucket size

2. **`executeHostLookup()`**: Simulates hostname lookup from IP address
   - **Vulnerability**: `hp->h_name` where `hp` can be NULL
   - **Risk**: NULL pointer dereference if host lookup fails

## Build Instructions
```bash
make clean && make
```

## Usage
```bash
# Run the service
./networkHandler

# Send data via stdin (this will cause NULL pointer dereference)
echo "0 invalid_ip_address" | ./networkHandler
```

## Security Impact
- **System Crashes**: NULL pointer dereference can cause program termination
- **Denial of Service**: Malicious input can crash the service
- **Memory Corruption**: Potential for further exploitation
- **Unexpected Behavior**: Invalid memory access can lead to undefined behavior

## Mitigation
- Always check pointers for NULL before dereferencing
- Implement proper error handling for failed operations
- Validate return values from system calls
- Use defensive programming practices
- Implement proper input validation

## Example Vulnerable Scenarios
1. **Sink 1**: User sends "0" → `bucket_size_ptr` becomes NULL → `*bucket_size_ptr` crashes
2. **Sink 2**: User sends "invalid_ip" → `hp` becomes NULL → `hp->h_name` crashes
