# CWE-606: Unchecked Input for Loop Condition

## Overview

This module demonstrates **CWE-606: Unchecked Input for Loop Condition**, a vulnerability where loop conditions are controlled by user input without proper validation, potentially leading to infinite loops, denial of service, or resource exhaustion.

## Vulnerability Details

### **Severity**: High (CVSS 7.5)
### **Type**: Control Flow
### **Impact**: Denial of Service, Resource Exhaustion, Infinite Loops

## Implementation

### **Source**: `recvmsg()`
- Receives UDP data on port 8084
- Data is **tainted** (user-controlled) and flows through the system

### **Transformers**:
1. **`parseBignumRequest()`**: Hash algorithm with bit operations
2. **`enrichBignumContext()`**: XOR + Linear transformations
3. **`prepareBignumExecution()`**: Bit shifts + OR operations

### **Sinks**:

#### **Sink 1: BIGNUM Conversion Loop**
```cpp
//SINK
// Unchecked loop condition - n can be manipulated by user input
while (n < get_bn_limit()) {
    l = (l << 8L) | *(s++);
    if (m-- == 0) {
        ret->d[--i] = l;
        l = 0;
        m = BN_BYTES - 1;
    }
    n++; // This can cause infinite loop if user sends large value
}
```
- Simulates OpenSSL's `BN_bin2bn()` function
- Loop condition `n < get_bn_limit()` uses user-controlled input
- `get_bn_limit()` returns `0x7FFFFFFF` (2GB)
- User can manipulate `n` to cause infinite loops

#### **Sink 2: BIGNUM Multiplication Loop**
```cpp
//SINK
// Unchecked loop condition - custom_bnbits can be manipulated by user input
for (; BN_BEGIN < custom_bnbits; BN_BEGIN++) {
    if (--nb <= 0) break;
    rr[1] = bn_mul_add_words(&(r[1]), a, na, b[1]);
    // ... more operations
}
```
- Simulates OpenSSL's `bn_mul_normal()` function
- Loop condition `BN_BEGIN < custom_bnbits` uses user-controlled input
- `custom_bnbits` comes from `udp_server_msg()` (tainted data)
- User can send large values to cause excessive iterations

## Attack Scenarios

1. **Infinite Loops**: Attacker sends large loop limit values
2. **Denial of Service**: System becomes unresponsive due to excessive processing
3. **Resource Exhaustion**: CPU and memory consumption skyrockets
4. **Buffer Overflows**: Large loop iterations can exceed buffer boundaries

## Mitigation

- Validate all loop conditions before entering loops
- Set reasonable upper limits for loop iterations
- Use bounded loops with maximum iteration counts
- Implement timeout mechanisms for long-running operations
- Sanitize all user input used in loop conditions

## Testing

```bash
# Build the application
make

# Test with UDP client (send data to port 8084)
echo "1073741824" | nc -u localhost 8084
```

## Files

- `bignumHandler.cpp` - UDP server using `recvmsg()` (SOURCE)
- `bignumEngine.cpp` - Transformers and sinks (CWE-606)
- `bignumHandler.h` - Handler header
- `bignumEngine.h` - Engine header
- `Makefile` - Build configuration

## Port

**UDP Port 8084** - Used for receiving BIGNUM data

## CWE-606 Specifics

This implementation demonstrates two classic CWE-606 patterns:

1. **While Loop with Unchecked Condition**: `while (n < get_bn_limit())`
2. **For Loop with Unchecked Limit**: `for (; BN_BEGIN < custom_bnbits; BN_BEGIN++)`

Both loops use user-controlled input without validation, making them vulnerable to manipulation that can cause system instability.
