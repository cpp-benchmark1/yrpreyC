CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = dataProcessorHandler
SOURCES = dataProcessorHandler.cpp dataProcessorEngine.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean deps run help

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "✅ Data Processing Manager compiled successfully!"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "🧹 Build artifacts cleaned"

deps:
	@echo "📦 Dependencies: g++, standard C++ libraries, file system libraries"

run: $(TARGET)
	@echo "🚀 Running Data Processing Manager..."
	./$(TARGET)

test: $(TARGET)
	@echo "🧪 Testing Data Processing Manager..."
	@echo "This will process data streams and create files"
	./$(TARGET)

help:
	@echo "📋 Available targets:"
	@echo "  all     - Build the application (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  deps    - Show dependencies"
	@echo "  run     - Build and run the application"
	@echo "  test    - Build and test the application"
	@echo "  help    - Show this help message"
