# CWE-789: Memory Allocation with Excessive Size Value

## Overview

This module demonstrates **CWE-789: Memory Allocation with Excessive Size Value**, a vulnerability where memory allocation functions receive excessively large size values that can lead to resource exhaustion, denial of service, or system crashes.

## Vulnerability Details

### **Severity**: High (CVSS 7.5)
### **Type**: Resource Management
### **Impact**: Denial of Service, System Instability

## Implementation

### **Source**: `recvfrom()`
- Receives UDP data on port 8083
- Data is **tainted** (user-controlled) and flows through the system

### **Transformers**:
1. **`parseCryptographicRequest()`**: Adds operation metadata
2. **`enrichCryptographicContext()`**: Adds timestamp and system info
3. **`prepareCryptographicExecution()`**: Applies final optimizations

### **Sinks**:

#### **Sink 1: BIGNUM Allocation**
```cpp
//SINK
BIGNUM *ret = (BIGNUM *)malloc(get_bn_limit()); // Excessive allocation size
```
- Simulates OpenSSL's `BN_new()` function
- Uses `get_bn_limit()` which returns `0x7FFFFFFF` (2GB)
- Can cause memory exhaustion

#### **Sink 2: Buffer Allocation**
```cpp
//SINK
buf = (unsigned char *)malloc(custom_bytes); // Excessive allocation size
```
- Uses `atoi()` on user-controlled data to determine allocation size
- Defaults to 1GB if invalid input
- Can cause system resource exhaustion

## Attack Scenarios

1. **Resource Exhaustion**: Attacker sends large size values via UDP
2. **Denial of Service**: System runs out of memory
3. **System Instability**: Large allocations can crash the service

## Mitigation

- Validate allocation sizes before calling `malloc()`
- Set reasonable upper limits for memory allocations
- Use `calloc()` for large allocations to detect overflow
- Implement memory quotas and limits

## Testing

```bash
# Build the application
make

# Test with UDP client (send data to port 8083)
echo "1073741824" | nc -u localhost 8083
```

## Files

- `cryptographicHandler.cpp` - UDP server using `recvfrom()` (SOURCE)
- `cryptographicEngine.cpp` - Transformers and sinks (CWE-789)
- `cryptographicHandler.h` - Handler header
- `cryptographicEngine.h` - Engine header
- `Makefile` - Build configuration

## Port

**UDP Port 8083** - Used for receiving cryptographic data
