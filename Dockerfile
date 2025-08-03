# Use an official lightweight Ubuntu image
FROM ubuntu:22.04

# Install build-essential package (includes g++, make, etc.)
RUN apt-get update && apt-get install -y build-essential

# Create a working directory inside the container
WORKDIR /usr/src/app

# Default command to keep the container running and open bash
CMD [ "bash" ]
