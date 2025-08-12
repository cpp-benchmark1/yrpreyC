CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = serverConfigurationHandler
SOURCES = serverConfigurationHandler.cpp serverConfigurationEngine.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean deps run help

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "✅ Server Configuration Manager compiled successfully!"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "🧹 Build artifacts cleaned"

deps:
	@echo "📦 Dependencies: g++, standard C++ libraries, socket libraries, file system libraries"

run: $(TARGET)
	@echo "🚀 Running Server Configuration Manager..."
	./$(TARGET)

test: $(TARGET)
	@echo "🧪 Testing Server Configuration Manager..."
	@echo "This will process configuration requests"
	./$(TARGET)

help:
	@echo "📋 Available targets:"
	@echo "  all     - Build the vulnerability (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  deps    - Show dependencies"
	@echo "  run     - Build and run the vulnerability"
	@echo "  test    - Build and test the vulnerability"
	@echo "  help    - Show this help message"
