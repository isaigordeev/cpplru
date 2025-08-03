FROM ubuntu:22.04

# Install base development tools and utilities
RUN apt-get update && \
    apt-get install -y \
        build-essential \
        clang \
        cmake \
        ninja-build \
        gdb \
        vim \
        git \
        sudo \
        openssh-server && \
    rm -rf /var/lib/apt/lists/*

# Create dev user and set password
RUN useradd -ms /bin/bash dev && echo "dev:devpass" | chpasswd && adduser dev sudo

# Setup SSH server
RUN mkdir /var/run/sshd

# Enable password authentication
RUN sed -i 's/#PasswordAuthentication yes/PasswordAuthentication yes/' /etc/ssh/sshd_config && \
    sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# Expose SSH port
EXPOSE 22

# Start SSH daemon when container starts
CMD ["/usr/sbin/sshd", "-D"]
