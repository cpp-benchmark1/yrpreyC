#include <string.h>

class NetworkPacketHandler {
public:
    static void handleIncomingPacket(char* buffer, size_t size, int index)
    {
        char dest_buffer[10];
        char buf[1] = {'X'};

        // First transformation: Process packet metadata and calculate offset
        if (size > 3) {
            // Extract packet flags and priority
            unsigned char packetFlags = buffer[0];
            unsigned char priority = buffer[1];
            
            // Calculate offset based on flags and priority
            if (packetFlags & 0x80) {  // High priority packet
                index = index + (priority * 3);  // Priority-based offset
            } else {  // Normal priority
                index = index - (priority * 2);  // Negative offset for normal
            }
            
            // Remove metadata and shift data
            for (size_t i = 0; i < size - 3; i++) {
                buffer[i] = buffer[i + 3];
            }
            size -= 3;
        }

        // Second transformation: Apply custom encoding
        if (size > 0) {
            // Calculate encoding-specific offset
            unsigned char encodingType = buffer[0];
            index = index + (encodingType * 4);  // Encoding type affects index
            
            // Apply custom encoding
            for (size_t i = 0; i < size; i++) {
                buffer[i] = buffer[i] ^ (0xAA + encodingType);  // Type-dependent XOR
            }
        }

        //SINK
        dest_buffer[index] = buf[0];  // Direct out-of-bounds write with attacker-controlled index
    }
}; 