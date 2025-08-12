# Makefile for CWE-676: Use of Potentially Dangerous Function
# Compiles the time processing vulnerability example

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = timeHandler
SOURCES = timeHandler.cpp timeEngine.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Main executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "✅ CWE-676 vulnerability compiled successfully!"

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
	@echo "🚀 Running CWE-676 vulnerability..."
	@echo "💡 This will start a server on port 8080"
	@echo "💡 Use 'nc localhost 8080' to connect and send data"
	./$(TARGET)

# Show help
help:
	@echo "CWE-676: Use of Potentially Dangerous Function - Build Commands:"
	@echo "  make        - Build the vulnerability"
	@echo "  make clean  - Clean build artifacts"
	@echo "  make run    - Build and run the vulnerability"
	@echo "  make help   - Show this help message"
	@echo ""
	@echo "Vulnerability Details:"
	@echo "  - Uses read() as source to receive network data"
	@echo "  - Processes data through 3 transformers"
	@echo "  - Uses gmtime() and localtime() as dangerous sinks"
	@echo "  - Demonstrates CWE-676: Use of Potentially Dangerous Function"

.PHONY: all clean deps run help
