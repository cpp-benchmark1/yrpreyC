CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = cryptographicHandler
SOURCES = cryptographicHandler.cpp cryptographicEngine.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean test help

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "✅ Cryptographic Processing Service compiled successfully!"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "🧹 Build artifacts cleaned"

test: $(TARGET)
	@echo "🧪 Testing Cryptographic Processing Service..."
	@echo "📡 Send UDP data to port 8083 to test the service"

help:
	@echo "🔐 Cryptographic Processing Service - CWE-789 Build System"
	@echo ""
	@echo "Available targets:"
	@echo "  all     - Build the application (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  test    - Build and test the application"
	@echo "  help    - Show this help message"
	@echo ""
	@echo "Usage:"
	@echo "  make        - Build the application"
	@echo "  make clean  - Clean build artifacts"
	@echo "  make test   - Test the application"
