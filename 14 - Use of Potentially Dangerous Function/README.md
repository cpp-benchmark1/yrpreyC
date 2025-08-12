# CWE-676: Use of Potentially Dangerous Function

## Overview

This vulnerability demonstrates **CWE-676: Use of Potentially Dangerous Function** by implementing a time processing service that uses thread-unsafe time functions. The application receives network data through a socket and processes it using dangerous functions that can lead to race conditions and memory corruption.

## Vulnerability Details

### CWE Classification
- **CWE ID**: 676
- **Category**: Use of Potentially Dangerous Function
- **Severity**: Medium
- **CVSS Score**: 5.5

### Dangerous Functions Used

#### Sink 1: `gmtime()`
```cpp
// BAD: using gmtime (not thread-safe, returns pointer to shared memory)
const time_t now_seconds = time(NULL);
struct tm *now = gmtime(&now_seconds);
```

**Problem**: `gmtime()` returns a pointer to static memory that is shared across all threads. Multiple threads calling this function simultaneously can cause race conditions and data corruption.

#### Sink 2: `localtime()`
```cpp
// UNSAFE: uses localtime (not thread-safe, returns pointer to shared memory)
time_t now_seconds = time(NULL);
struct tm *local = localtime(&now_seconds);
```

**Problem**: Similar to `gmtime()`, `localtime()` returns a pointer to shared static memory, making it unsafe for multi-threaded applications.

## Architecture

### Data Flow
```
Network Input (read()) → Transformers → Dangerous Sinks
     ↓                        ↓           ↓
  Socket Data         3 Transformers   gmtime()/localtime()
```

### Components

1. **Source**: `timeHandler.cpp`
   - Uses `read()` to receive data from network socket
   - Receives untrusted user input without sanitization

2. **Transformers**:
   - `parseTimeRequest()`: Adds metadata and transforms structure
   - `enrichTimeContext()`: Adds timestamp and system information
   - `prepareTimeExecution()`: Applies final optimizations

3. **Sinks**:
   - `executeMorningCheck()`: Uses `gmtime()` (thread-unsafe)
   - `executeTimeDisplay()`: Uses `localtime()` (thread-unsafe)

## Exploitation

### Race Condition Attack
1. Start multiple threads simultaneously
2. Each thread calls the dangerous time functions
3. Observe corrupted time data or crashes
4. Potential privilege escalation through memory corruption

### Memory Corruption
- Multiple threads accessing shared static memory
- Overwriting of time structure data
- Potential buffer overflow in time formatting

## Mitigation

### Safe Alternatives
```cpp
// Use thread-safe alternatives
struct tm timeinfo;
time_t now = time(NULL);
gmtime_r(&now, &timeinfo);  // Thread-safe version
localtime_r(&now, &timeinfo); // Thread-safe version
```

### Best Practices
1. **Never use `gmtime()` or `localtime()` in multi-threaded applications**
2. **Use `gmtime_r()` and `localtime_r()` for thread safety**
3. **Implement proper input validation and sanitization**
4. **Use RAII and smart pointers for memory management**

## Building and Running

### Compilation
```bash
make
```

### Running
```bash
make run
```

### Testing
```bash
# In another terminal
nc localhost 8080
# Send any data to trigger the vulnerability
```

### Cleanup
```bash
make clean
```

## Files

- `timeHandler.cpp` - Main application with socket source
- `timeEngine.h` - Header file with function declarations
- `timeEngine.cpp` - Implementation with transformers and sinks
- `Makefile` - Build configuration
- `README.md` - This documentation

## Security Impact

- **Confidentiality**: Potential exposure of system time information
- **Integrity**: Memory corruption through race conditions
- **Availability**: Application crashes due to memory issues
- **Privilege Escalation**: Potential code execution through memory corruption

## References

- [CWE-676: Use of Potentially Dangerous Function](https://cwe.mitre.org/data/definitions/676.html)
- [POSIX Thread Safety](https://pubs.opengroup.org/onlinepubs/9699919799/functions/gmtime.html)
- [Time Functions Security](https://man7.org/linux/man-pages/man3/gmtime.3.html)
