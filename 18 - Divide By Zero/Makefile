CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = resourceMonitorHandler
SOURCES = resourceMonitorHandler.cpp resourceMonitorEngine.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "✅ Resource Monitor Service compiled successfully!"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "🧹 Build artifacts cleaned"

help:
	@echo "Available targets:"
	@echo "  all     - Build the resource monitor handler"
	@echo "  clean   - Remove build artifacts"
	@echo "  help    - Show this help message"
