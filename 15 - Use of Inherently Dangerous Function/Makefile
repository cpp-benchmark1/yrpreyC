# Makefile for CWE-242: Use of Inherently Dangerous Function
# Compiles the file metadata vulnerability example

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = fileMetadataHandler
SOURCES = fileMetadataHandler.cpp fileMetadataEngine.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Main executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "✅ CWE-242 vulnerability compiled successfully!"

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "🧹 Build artifacts cleaned"

# Install dependencies (if needed)
deps:
	@echo "📦 No external dependencies required for this vulnerability"

# Run the vulnerability (for testing)
run: $(TARGET)
	@echo "🚀 Running CWE-242 vulnerability..."
	@echo "💡 This will start a server on port 8081"
	@echo "💡 Use 'nc localhost 8081' to connect and send metadata"
	@echo "💡 The application will prompt for filename and category using gets()"
	./$(TARGET)

# Test with netcat
test: $(TARGET)
	@echo "🧪 Testing CWE-242 vulnerability..."
	@echo "💡 Starting server in background..."
	@./$(TARGET &
	@echo "💡 Server started. Use 'nc localhost 8081' to test"
	@echo "💡 Send any data, then enter long strings for filename/category to trigger overflow"

# Show help
help:
	@echo "CWE-242: Use of Inherently Dangerous Function - Build Commands:"
	@echo "  make        - Build the vulnerability"
	@echo "  make clean  - Clean build artifacts"
	@echo "  make run    - Build and run the vulnerability"
	@echo "  make test   - Build and test with netcat"
	@echo "  make help   - Show this help message"
	@echo ""
	@echo "Vulnerability Details:"
	@echo "  - Uses readv() as source to receive network metadata"
	@echo "  - Processes data through 3 transformers"
	@echo "  - Uses gets() as dangerous sink (CWE-242)"
	@echo "  - Demonstrates buffer overflow through gets() function"

.PHONY: all clean deps run test help
