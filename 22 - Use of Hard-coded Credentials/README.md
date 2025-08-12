# CWE-798: Use of Hard-coded Credentials

## Overview
This implementation demonstrates CWE-798, which occurs when hardcoded credentials are embedded in source code. This vulnerability allows attackers to gain unauthorized access to systems by extracting credentials from the compiled binary or source code.

## Vulnerability Details
The vulnerability manifests in two main areas:

1. **Source**: Hardcoded database credentials in the source code
2. **Sinks**: Two functions that use these hardcoded credentials for authentication and connection

### Hardcoded Credentials Used:
- **Host**: `analytics.enterprise.com`
- **Username**: `monitoring_user`
- **Password**: `Kj8mN2pQ9vR5tX7wZ1aB3cD6eF8gH`
- **Database**: `performance_metrics`

## Architecture

### Source (`databaseConnectionHandler.cpp`)
- Contains hardcoded database credentials
- Packages credentials into a connection string
- Passes data to the engine for processing

### Transformers
1. **`parseConnectionRequest`**: Adds metadata about the connection type
2. **`enrichConnectionContext`**: Adds timestamp and system information
3. **`prepareConnectionExecution`**: Applies final formatting and encryption markers

### Sinks
1. **`executeDatabaseAuthentication`**: Uses hardcoded credentials for authentication
2. **`executeDatabaseConnection`**: Uses hardcoded credentials for database connection

## Data Flow
```
Hardcoded Credentials (Source) 
    ↓
parseConnectionRequest (Transformer 1)
    ↓
enrichConnectionContext (Transformer 2)
    ↓
prepareConnectionExecution (Transformer 3)
    ↓
executeDatabaseAuthentication (Sink 1) + executeDatabaseConnection (Sink 2)
```

## Exploitation
An attacker can:
1. Extract hardcoded credentials from the binary
2. Use credentials to access the database directly
3. Perform unauthorized database operations
4. Access sensitive data or modify database contents

## Mitigation
- Store credentials in environment variables
- Use secure credential management systems
- Implement proper authentication mechanisms
- Use encrypted configuration files
- Implement credential rotation policies

## Build and Run

### Prerequisites
- g++ compiler
- Standard C++ libraries
- Socket libraries

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
22 - Use of Hard-coded Credentials/
├── databaseConnectionHandler.h      # Header for handler
├── databaseConnectionHandler.cpp    # Source implementation
├── databaseConnectionEngine.h       # Header for engine
├── databaseConnectionEngine.cpp     # Transformers and sinks
├── Makefile                        # Build configuration
└── README.md                       # This file
```

## Security Impact
- **Severity**: High
- **CVSS Score**: 9.8 (Critical)
- **Attack Vector**: Local/Remote
- **Privileges Required**: None
- **User Interaction**: None

## Notes
- This is a demonstration implementation for educational purposes
- Do not use hardcoded credentials in production systems
- Always follow security best practices for credential management
