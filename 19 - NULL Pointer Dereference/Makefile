CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = networkHandler
SOURCES = networkHandler.cpp networkEngine.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "✅ Network Processing Service compiled successfully!"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "🧹 Build artifacts cleaned"

help:
	@echo "Available targets:"
	@echo "  all     - Build the network handler"
	@echo "  clean   - Remove build artifacts"
	@echo "  help    - Show this help message"
