# CWE-369: Divide By Zero

## Description
This module demonstrates divide by zero vulnerabilities in resource monitoring operations. The implementation shows how user-controlled input can lead to division by zero, causing crashes or unexpected behavior.

## Implementation Details

### Source
- **Function**: `recvfrom()` on UDP port 8085
- **Purpose**: Receives resource monitoring data from user input
- **Location**: `resourceMonitorHandler.cpp` - `resourceMonitorHandler_processResourceStream()`

### Transformers
1. **`parseResourceRequest()`**: Adds operation type and length metadata
2. **`enrichResourceContext()`**: Adds timestamp and system information
3. **`prepareResourceExecution()`**: Applies final optimizations and enhancements

### Sinks
1. **`executeResourceCalculation()`**: Divides total data transfer by bandwidth divisor
   - **Vulnerability**: `total_data / bandwidth_divisor` where `bandwidth_divisor` comes from user input
   - **Risk**: Divide by zero if user sends "0" or invalid divisor value

2. **`executeUsageComputation()`**: Distributes CPU load across cores
   - **Vulnerability**: `total_load / cpu_cores` where `cpu_cores` comes from user input
   - **Risk**: Divide by zero if user sends "0" or invalid core count

## Build Instructions
```bash
make clean && make
```

## Usage
```bash
# Set environment variables (optional)
export TOTAL_DATA_TRANSFER=8192
export TOTAL_CPU_LOAD=100

# Run the service
./resourceMonitorHandler

# Send data via UDP (in another terminal)
echo "0" | nc -u localhost 8085  # This will cause divide by zero
```

## Security Impact
- **System Crashes**: Division by zero can cause program termination
- **Denial of Service**: Malicious input can crash the service
- **Unexpected Behavior**: Invalid calculations can lead to incorrect results

## Mitigation
- Validate divisor values before division
- Check for zero values and handle gracefully
- Implement proper input validation
- Use safe division functions with error handling
