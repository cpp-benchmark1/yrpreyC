#include <string.h>

class DataFormatHandler {
public:
    static void handleDataFormat(char* buffer, size_t size, int index)
    {
        char dest_buffer[10];
        char buf[1] = {'Y'};

        // First transformation: Process format metadata and calculate offset
        if (size > 2) {
            // Extract format type and compression level
            unsigned char formatType = buffer[0];
            unsigned char compressionLevel = buffer[1];
            
            // Calculate offset based on format type and compression
            if (formatType == 0x10) {  // Compressed format
                if (compressionLevel > 5) {  // High compression
                    index = index + 12;  // High compression offset
                } else {  // Low compression
                    index = index + 6;  // Low compression offset
                }
            } else if (formatType == 0x20) {  // Uncompressed format
                if (compressionLevel > 5) {  // High compression
                    index = index - 8;  // High compression offset
                } else {  // Low compression
                    index = index - 4;  // Low compression offset
                }
            }
            
            // Remove format header
            for (size_t i = 0; i < size - 2; i++) {
                buffer[i] = buffer[i + 2];
            }
            size -= 2;
        }

        //SINK
        dest_buffer[index] = buf[0];  // Direct out-of-bounds write with attacker-controlled index
    }
}; 