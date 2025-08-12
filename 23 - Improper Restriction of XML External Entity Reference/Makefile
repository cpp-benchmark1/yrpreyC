CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I/usr/include/libxml2
TARGET = deviceConfigHandler
SOURCES = deviceConfigHandler.cpp deviceConfigEngine.cpp
OBJECTS = $(SOURCES:.cpp=.o)
LIBS = -lxml2

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)
	@echo "✅ Device Configuration Service compiled successfully!"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "🧹 Build artifacts cleaned"

help:
	@echo "Available targets:"
	@echo "  all     - Build the device configuration handler"
	@echo "  clean   - Remove build artifacts"
	@echo "  help    - Show this help message"
