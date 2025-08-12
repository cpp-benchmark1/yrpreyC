# CWE Mapping - YrpreyC Framework

## Overview
This document maps the Common Weakness Enumeration (CWE) identifiers to their corresponding vulnerability implementations in the YrpreyC framework.

## Implemented Vulnerabilities

### Core Memory Vulnerabilities
| Directory | CWE ID | CWE Name | Status | Description |
|-----------|---------|----------|---------|-------------|
| `01 - Buffer Overflow Vanilla` | CWE-119 | Buffer Overflow | ✅ Implemented | Classic buffer overflow vulnerability |
| `02 - Injection Flaws` | CWE-78 | OS Command Injection | ✅ Implemented | Command injection through user input |
| `03 - Format String` | CWE-134 | Use of Externally-Controlled Format String | ✅ Implemented | Format string vulnerability |
| `04 - Memory Leaks` | CWE-401 | Missing Release of Memory | ✅ Implemented | Memory leak demonstration |
| `05 - Improper Null Termination` | CWE-170 | Improper Null Termination | ✅ Implemented | Null termination issues |
| `06 - Heap Overflow` | CWE-122 | Heap-based Buffer Overflow | ✅ Implemented | Heap overflow vulnerability |
| `07 - Integer Overflow` | CWE-190 | Integer Overflow or Wraparound | ✅ Implemented | Integer overflow demonstration |
| `08 - Integer Underflow` | CWE-191 | Integer Underflow | ✅ Implemented | Integer underflow demonstration |
| `09 - Out of Buffer Bounds Write` | CWE-787 | Out-of-bounds Write | ✅ Implemented | Buffer bounds violation |
| `10 - SQL Injection` | CWE-89 | SQL Injection | ✅ Implemented | SQL injection vulnerability |
| `11 - SSRF` | CWE-918 | Server-Side Request Forgery | ✅ Implemented | SSRF vulnerability |
| `12 - Code Injection` | CWE-94 | Code Injection | ✅ Implemented | Dynamic code execution |
| `13 - NoSQL Injection` | CWE-943 | Improper Neutralization of Special Elements | ✅ Implemented | NoSQL injection |
| `14 - Use of Potentially Dangerous Function` | CWE-676 | Use of Potentially Dangerous Function | ✅ Implemented | Thread-unsafe time functions |

### New Vulnerabilities (Ready for Implementation)
| Directory | CWE ID | CWE Name | Status | Description |
|-----------|---------|----------|---------|-------------|
| `15 - Use of Inherently Dangerous Function` | CWE-242 | Use of Inherently Dangerous Function | 🚧 Ready | Functions that are inherently dangerous |
| `16 - Time-of-check Time-of-use Race Condition` | CWE-367 | Time-of-check Time-of-use (TOCTOU) Race Condition | ✅ Implemented | Race condition vulnerability |
| `17 - Out-of-bounds Read` | CWE-125 | Out-of-bounds Read | 🚧 Ready | Reading beyond buffer boundaries |
| `18 - Divide By Zero` | CWE-369 | Divide By Zero | 🚧 Ready | Division by zero vulnerability |
| `19 - NULL Pointer Dereference` | CWE-476 | NULL Pointer Dereference | 🚧 Ready | Null pointer dereference |
| `20 - Unchecked Input for Loop Condition` | CWE-606 | Unchecked Input for Loop Condition | 🚧 Ready | Loop condition validation |
| `21 - Memory Allocation with Excessive Size Value` | CWE-789 | Memory Allocation with Excessive Size Value | ✅ Implemented | Excessive memory allocation |
| `22 - Use of Hard-coded Credentials` | CWE-798 | Use of Hard-coded Credentials | ✅ Implemented | Hard-coded credentials |
| `23 - Improper Restriction of XML External Entity Reference` | CWE-611 | Improper Restriction of XML External Entity Reference | 🚧 Ready | XXE vulnerability |
| `24 - Incorrect Permission Assignment for Critical Resource` | CWE-732 | Incorrect Permission Assignment for Critical Resource | ✅ Implemented | Permission assignment issues |

## CWE Categories Covered

### Memory Management
- **CWE-119**: Buffer Overflow
- **CWE-122**: Heap-based Buffer Overflow
- **CWE-125**: Out-of-bounds Read
- **CWE-170**: Improper Null Termination
- **CWE-401**: Missing Release of Memory
- **CWE-476**: NULL Pointer Dereference
- **CWE-787**: Out-of-bounds Write
- **CWE-789**: Memory Allocation with Excessive Size Value

### Input Validation
- **CWE-78**: OS Command Injection
- **CWE-89**: SQL Injection
- **CWE-134**: Use of Externally-Controlled Format String
- **CWE-606**: Unchecked Input for Loop Condition
- **CWE-611**: Improper Restriction of XML External Entity Reference
- **CWE-943**: Improper Neutralization of Special Elements

### Numeric Operations
- **CWE-190**: Integer Overflow or Wraparound
- **CWE-191**: Integer Underflow
- **CWE-369**: Divide By Zero

### Function Usage
- **CWE-676**: Use of Potentially Dangerous Function
- **CWE-242**: Use of Inherently Dangerous Function

### Race Conditions
- **CWE-367**: Time-of-check Time-of-use (TOCTOU) Race Condition

### Security Misconfiguration
- **CWE-732**: Incorrect Permission Assignment for Critical Resource
- **CWE-798**: Use of Hard-coded Credentials

### Network Security
- **CWE-918**: Server-Side Request Forgery

### Code Execution
- **CWE-94**: Code Injection

## Implementation Status

- **✅ Implemented**: 18 vulnerabilities
- **🚧 Ready for Implementation**: 6 vulnerabilities
- **📊 Total**: 24 vulnerabilities

## Next Steps

1. **Priority 1**: Implement CWE-125 (Out-of-bounds Read) - Critical memory vulnerability
2. **Priority 2**: Implement CWE-476 (NULL Pointer Dereference) - Common crash vulnerability
3. **Priority 3**: Implement CWE-369 (Divide By Zero) - Simple but effective vulnerability
4. **Priority 4**: Implement remaining CWEs following the established pattern

## Building and Testing

```bash
# Build all vulnerabilities
./docker-build.sh

# Compile specific vulnerability
docker run --rm -v $(pwd):/workspace yrpreyc bash -c "cd '15 - Use of Inherently Dangerous Function' && make"

# Run specific vulnerability
docker run --rm -v $(pwd):/workspace yrpreyc bash -c "cd '15 - Use of Inherently Dangerous Function' && make run"
```

## References

- [CWE Official Website](https://cwe.mitre.org/)
- [OWASP Top 10](https://owasp.org/www-project-top-ten/)
- [MITRE CWE Database](https://cwe.mitre.org/data/index.html)
