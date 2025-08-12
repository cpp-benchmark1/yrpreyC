CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = databaseConnectionHandler
SOURCES = databaseConnectionHandler.cpp databaseConnectionEngine.cpp
OBJECTS = $(SOURCES:.cpp=.o)
LIBS = -lmysqlclient -lldap

.PHONY: all clean deps run help

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)
	@echo "✅ CWE-798 vulnerability compiled successfully!"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "🧹 Build artifacts cleaned"

deps:
	@echo "📦 Dependencies: g++, standard C++ libraries, MySQL client library, LDAP library"

run: $(TARGET)
	@echo "🚀 Running CWE-798 vulnerability..."
	./$(TARGET)

test: $(TARGET)
	@echo "🧪 Testing CWE-798 vulnerability..."
	@echo "This will demonstrate hardcoded credentials usage"
	./$(TARGET)

help:
	@echo "📋 Available targets:"
	@echo "  all     - Build the vulnerability (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  deps    - Show dependencies"
	@echo "  run     - Build and run the vulnerability"
	@echo "  test    - Build and test the vulnerability"
	@echo "  help    - Show this help message"
