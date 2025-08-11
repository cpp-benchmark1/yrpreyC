# CWE-367: Time-of-check Time-of-use Race Condition

## Overview
This implementation demonstrates CWE-367, which occurs when there is a time gap between checking a condition and using the result of that check. This race condition allows attackers to manipulate the state of resources between the check and use phases, potentially leading to security vulnerabilities.

## Vulnerability Details
The vulnerability manifests in two main areas:

1. **Source**: Network data received via `recvfrom()`
2. **Sinks**: Two functions that demonstrate TOCTOU race conditions

### Race Condition Pattern:
- **TIME OF CHECK**: Verify file existence and properties
- **RACE CONDITION WINDOW**: Attacker can manipulate file state
- **TIME OF USE**: Use the file assuming it's still in the checked state

## Architecture

### Source (`serverConfigurationHandler.cpp`)
- Uses `recvfrom()` to receive configuration data over UDP
- Listens on port 8082 for incoming configuration requests
- Passes received data to the engine for processing

### Transformers
1. **`parseConfigurationRequest`**: Adds metadata about the configuration type
2. **`enrichConfigurationContext`**: Adds timestamp and system information
3. **`prepareConfigurationExecution`**: Applies final formatting and validation markers

### Sinks
1. **`executeConfigurationRetrieval`**: Demonstrates TOCTOU with file operations
2. **`executeFileContentRetrieval`**: Demonstrates TOCTOU with file reading

## Data Flow
```
Network Data (recvfrom) → Transformers → Sinks (TOCTOU Race Conditions)
```

## Race Condition Details

### Sink 1: Configuration Retrieval
```cpp
// TIME OF CHECK
if (stat(filename, &st) != 0) { ... }

// RACE CONDITION WINDOW
if (remove(filename) != 0) { ... }
if (symlink(user_input, filename) != 0) { ... }

// TIME OF USE
//SINK
FILE *f = fopen(filename, "r");  // File could be different now!
```

### Sink 2: File Content Retrieval
```cpp
// TIME OF CHECK
if (stat(filename, &st) != 0) { ... }

// RACE CONDITION WINDOW
// Attacker can replace file with malicious content

// TIME OF USE
//SINK
FILE *f = fopen(filename, "r");  // File could be malicious now!
```

## Exploitation
An attacker can:
1. Send configuration data via UDP
2. Manipulate file system during race condition window
3. Replace legitimate files with malicious content
4. Bypass security checks by changing file state
5. Execute arbitrary code or access sensitive data

## Mitigation
- Use atomic operations when possible
- Implement proper file locking mechanisms
- Use secure file handling libraries
- Minimize time between check and use
- Implement proper access controls
- Use secure file paths and validation

## Build and Run

### Prerequisites
- g++ compiler
- Standard C++ libraries
- Socket libraries
- File system libraries

### Compilation
```bash
make
```

### Clean Build
```bash
make clean
make
```

### Run
```bash
make run
```

### Test
```bash
make test
```

## File Structure
```
16 - Time-of-check Time-of-use Race Condition/
├── serverConfigurationHandler.h      # Header for handler
├── serverConfigurationHandler.cpp    # Source implementation
├── serverConfigurationEngine.h       # Header for engine
├── serverConfigurationEngine.cpp     # Transformers and sinks
├── Makefile                         # Build configuration
└── README.md                        # This file
```

## Security Impact
- **Severity**: High
- **CVSS Score**: 7.5 (High)
- **Attack Vector**: Local/Remote
- **Privileges Required**: Low
- **User Interaction**: None

## Notes
- This is a demonstration implementation for educational purposes
- Do not use race condition patterns in production systems
- Always implement proper file handling and validation
- Consider using secure alternatives for file operations
