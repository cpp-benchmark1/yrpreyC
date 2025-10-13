# YrpreyC Makefile with Docker support
# Use 'make' to build with Docker, 'make clean' to clean up

.PHONY: all build clean run-docker help

# Default target
all: build
SHELL := /bin/bash

build:
ifeq ($(COVERITY_BUILD_MODE),host)
	@echo "🏗️ Building all subdirectories on host for Coverity..."
	@find . -mindepth 1 -maxdepth 1 -type d ! -name ".*" -print | while IFS= read -r d; do \
		if [ -f "$$d/Makefile" ]; then \
			echo "---- Building in: $$d ----"; \
			$(MAKE) -C "$$d" clean >/dev/null 2>&1 || true; \
			$(MAKE) -C "$$d" -B -j$$(nproc) || echo "Build failed in $$d, continuing..."; \
		fi; \
	done
else
	@echo "🐳 Building YrpreyC with Docker..."
	@./docker-build.sh
endif

# Build using Docker or directly (for Coverity)
build:
ifeq ($(COVERITY_BUILD_MODE),host)
	@echo "🏗️ Building all subdirectories on host for Coverity..."
	@find . -mindepth 1 -maxdepth 1 -type d ! -name ".*" -print | while IFS= read -r d; do \
		if [ -f "$$d/Makefile" ]; then \
			echo "---- Building in: $$d ----"; \
			$(MAKE) -C "$$d" clean >/dev/null 2>&1 || true; \
			$(MAKE) -C "$$d" -B -j$$(nproc) || echo "Build failed in $$d, continuing..."; \
		fi; \
	done
else
	@echo "🐳 Building YrpreyC with Docker..."
	@./docker-build.sh
endif

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
	@echo ""
	@echo "Vulnerabilities available:"
	@echo "  - CWE-676: Use of Potentially Dangerous Function (gmtime/localtime)"
	@echo "  - Buffer Overflow, Injection Flaws, Format String, and more..."
