# YrpreyC Makefile with Docker support
# Use 'make' to build with Docker, 'make clean' to clean up

.PHONY: all build clean run-docker help

# Default target
all: build

# Build using Docker
build:
	@echo "🐳 Building YrpreyC with Docker..."
	@./docker-build.sh

# Alternative: direct Docker commands
docker-build:
	@echo "📦 Building Docker image..."
	docker build -t yrpreyc .
	@echo "🔨 Compiling projects..."
	docker run --rm -v "$(PWD):/workspace" yrpreyc ./build.sh

# Run interactive Docker shell
run-docker:
	@echo "🚀 Starting interactive Docker shell..."
	docker run --rm -it -v "$(PWD):/workspace" yrpreyc bash

# Clean up Docker image
clean:
	@echo "🧹 Cleaning up Docker image..."
	docker rmi yrpreyc 2>/dev/null || true
	@echo "✅ Cleanup completed"

# Show help
help:
	@echo "YrpreyC Build Commands:"
	@echo "  make          - Build project using Docker (recommended)"
	@echo "  make docker-build - Build using direct Docker commands"
	@echo "  make run-docker   - Start interactive Docker shell"
	@echo "  make clean        - Remove Docker image"
	@echo "  make help         - Show this help message"
	@echo ""
	@echo "Quick commands:"
	@echo "  ./docker-build.sh - Run the build script directly"
	@echo "  docker build -t yrpreyc . - Build Docker image only"
	@echo "  docker run --rm -v \$(pwd):/workspace yrpreyc ./build.sh - Compile only"
