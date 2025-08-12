# CWE-611: Improper Restriction of XML External Entity Reference

## Description
This module demonstrates XML External Entity (XXE) vulnerabilities in device configuration processing operations. The implementation shows how user-controlled input can lead to XXE attacks when XML parsing is configured with dangerous flags.

## Implementation Details

### Source
- **Function**: `read()` from `/dev/stdin`
- **Purpose**: Receives device configuration data from user input
- **Location**: `deviceConfigHandler.cpp` - `deviceConfigHandler_processDeviceStream()`

### Transformers
1. **`parseDeviceRequest()`**: Extracts numerical values from source input using mathematical operations
2. **`enrichDeviceContext()`**: Applies XOR with magic number and bit shifting
3. **`prepareDeviceExecution()`**: Performs modular arithmetic and bit operations

### Sinks
1. **`executeDeviceConfigProcessing()`**: Processes device configuration XML files
   - **Vulnerability**: Simulates `xmlReadFile()` with dangerous flags `XML_PARSE_DTDLOAD | XML_PARSE_NOENT`
   - **Risk**: XXE attack if user provides malicious XML with external entities

2. **`executeNetworkConfigParsing()`**: Parses network configuration XML files
   - **Vulnerability**: Simulates `xmlReadFile()` with dangerous flags `XML_PARSE_DTDLOAD | XML_PARSE_NOENT`
   - **Risk**: XXE attack if user provides malicious XML with external entities

## Build Instructions
```bash
make clean && make
```

## Usage
```bash
# Run the service
./deviceConfigHandler

# Send data via stdin (this will cause XXE vulnerability)
echo "malicious_xml_file.xml" | ./deviceConfigHandler
```

## Security Impact
- **Information Disclosure**: XXE can read local files on the system
- **Server-Side Request Forgery**: XXE can make HTTP requests to internal services
- **Denial of Service**: XXE can cause resource exhaustion
- **Remote Code Execution**: In some cases, XXE can lead to RCE

## Mitigation
- Disable DTD processing (`XML_PARSE_NODTD`)
- Disable external entity expansion (`XML_PARSE_NOENT`)
- Use secure XML parsers
- Validate and sanitize XML input
- Implement proper access controls

## Example Vulnerable XML
```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE test [
  <!ENTITY xxe SYSTEM "file:///etc/passwd">
]>
<test>&xxe;</test>
```

## XXE Attack Vectors
1. **File Reading**: `file:///etc/passwd`
2. **Internal Network Scanning**: `http://internal-service:8080`
3. **Resource Exhaustion**: Billion laughs attack
4. **Out-of-Band Data Exfiltration**: DNS/HTTP requests
