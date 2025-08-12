CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = connectionPoolHandler
SOURCES = connectionPoolHandler.cpp connectionPoolEngine.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "✅ Connection Pool Service compiled successfully!"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "🧹 Build artifacts cleaned"

.PHONY: all clean
