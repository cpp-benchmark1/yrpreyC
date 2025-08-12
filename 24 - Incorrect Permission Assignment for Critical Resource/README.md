# CWE-732: Incorrect Permission Assignment for Critical Resource

## Overview
This implementation demonstrates CWE-732, which occurs when permissions are incorrectly assigned to critical resources, allowing unauthorized access or modification. This vulnerability can lead to privilege escalation, data exposure, or system compromise.

## Vulnerability Details
The vulnerability manifests in two main areas:

1. **Source**: Data received via `read()` from standard input
2. **Sinks**: Two functions that create files with unsafe permissions

### Unsafe Permission Patterns:
- **Sink 1**: Log files with permissions 777 (world-writable)
- **Sink 2**: Binary files with permissions 666 (world-readable/writable)

## Architecture

### Source (`dataProcessorHandler.cpp`)
- Uses `read()` to receive data from standard input
- Processes incoming data streams
- Passes data to the engine for processing

### Transformers
1. **`parseDataRequest`**: Adds metadata about the data type
2. **`enrichDataContext`**: Adds timestamp and system information
3. **`prepareDataExecution`**: Applies final formatting and validation markers

### Sinks
1. **`executeLogFileCreation`**: Creates log files with unsafe permissions (777)
2. **`executeBinaryFileCreation`**: Creates binary files with unsafe permissions (666)

## Data Flow
```
Standard Input (read) → Transformers → Sinks (Unsafe File Creation)
```

## Permission Assignment Details

### Sink 1: Log File Creation
```cpp
//SINK
// Create log file with unsafe permissions (777) - CWE-732
int fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0777);
```
- **File Path**: `/var/logs/log_YYYYMMDD_HHMMSS.log`
- **Permissions**: 777 (world-readable, writable, executable)
- **Risk**: Any user can read, write, or execute the log file

### Sink 2: Binary File Creation
```cpp
//SINK
// Create binary file with unsafe permissions (666) - CWE-732
int fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0666);
```
- **File Path**: `/usr/local/bin/data_YYYYMMDD_HHMMSS.bin`
- **Permissions**: 666 (world-readable and writable)
- **Risk**: Any user can read or modify the binary file

## Exploitation
An attacker can:
1. Send malicious data via standard input
2. Trigger creation of files with unsafe permissions
3. Read sensitive information from log files
4. Modify binary files to execute malicious code
5. Gain unauthorized access to system resources
6. Perform privilege escalation attacks

## Mitigation
- Use appropriate file permissions (644 for files, 755 for directories)
- Implement proper access controls and user separation
- Use umask to restrict default permissions
- Implement file ownership restrictions
- Use secure file creation patterns
- Audit file permissions regularly

## Build and Run

### Prerequisites
- g++ compiler
- Standard C++ libraries
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
24 - Incorrect Permission Assignment for Critical Resource/
├── dataProcessorHandler.h      # Header for handler
├── dataProcessorHandler.cpp    # Source implementation
├── dataProcessorEngine.h       # Header for engine
├── dataProcessorEngine.cpp     # Transformers and sinks
├── Makefile                    # Build configuration
└── README.md                   # This file
```

## Security Impact
- **Severity**: High
- **CVSS Score**: 7.5 (High)
- **Attack Vector**: Local
- **Privileges Required**: Low
- **User Interaction**: None

## Notes
- This is a demonstration implementation for educational purposes
- Do not use unsafe permission patterns in production systems
- Always follow the principle of least privilege
- Implement proper file permission management
- Consider using secure alternatives for file operations
