#!/bin/bash

# YrpreyC Docker Build Script
# Este script automatiza o processo de build usando Docker

set -e  # Exit on any error

echo "🐳 Building YrpreyC with Docker..."

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check if Docker is running
if ! docker info > /dev/null 2>&1; then
    echo -e "${RED}❌ Docker is not running. Please start Docker first.${NC}"
    exit 1
fi

# Build the Docker image
echo -e "${YELLOW}📦 Building Docker image...${NC}"
docker build -t yrpreyc .

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ Docker image built successfully!${NC}"
else
    echo -e "${RED}❌ Failed to build Docker image${NC}"
    exit 1
fi

# Build completed successfully
echo -e "${GREEN}✅ Docker image built successfully!${NC}"
echo -e "${YELLOW}📋 Image 'yrpreyc' is ready for use${NC}"

echo -e "${GREEN}🎉 YrpreyC Docker image built successfully!${NC}"
echo ""
echo "💡 To compile and run projects:"
echo "   docker run --rm -v \$(pwd):/workspace yrpreyc ./build.sh"
echo ""
echo "💡 To access interactive shell:"
echo "   docker run --rm -it -v \$(pwd):/workspace yrpreyc bash"
echo ""
echo "💡 To clean up Docker image:"
echo "   docker rmi yrpreyc"
