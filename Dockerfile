# Use Ubuntu as base image
FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install basic build tools and dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    g++ \
    git \
    wget \
    curl \
    unzip \
    python3 \
    python3-pip \
    libmysqlclient-dev \
    libldap2-dev \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Install CodeQL CLI
RUN wget https://github.com/github/codeql-action/releases/latest/download/codeql-bundle-linux64.tar.gz \
    && tar -xvzf codeql-bundle-linux64.tar.gz \
    && rm codeql-bundle-linux64.tar.gz \
    && mv codeql /opt/codeql

# Add CodeQL to PATH
ENV PATH="/opt/codeql:${PATH}"

# Create directory for Coverity tools
RUN mkdir -p /opt/coverity

# Set working directory
WORKDIR /workspace

# Copy build script
COPY build.sh /workspace/
RUN chmod +x /workspace/build.sh

# Default command
CMD ["/bin/bash"] 