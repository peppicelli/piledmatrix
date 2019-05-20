# This Dockerfile is used to build an environment where cross compilation
# for Raspbian rt is made possible.

FROM ubuntu:18.04
LABEL maintainer="daniel.peppicelli@gmail.com"

# By default, use user ID 1000 (should be the same as default ubuntu user). 
# If not, replace args on the command line.
ARG UNAME=build
ARG UID=1000
ARG GID=1000

# Install all needed packages
RUN apt-get update && \
  apt-get install -f -y --no-install-recommends --fix-missing \
    git \
    rsync \
    cmake \
    make \
    curl \
    doxygen \
    graphviz \
    ca-certificates && \
  rm -rf /var/lib/apt/lists/*
RUN update-ca-certificates

# Create local user with sudo rights and without password
RUN groupadd -g $GID $UNAME
RUN useradd -m -u $UID -g $GID -s /bin/bash $UNAME && \
      echo "$UNAME:$UNAME" | chpasswd && adduser $UNAME sudo
RUN echo "$UNAME ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

# Install the cross compiler
RUN mkdir -p /opt/raspberry/tools && \
  git clone --depth 1 https://github.com/raspberrypi/tools.git opt/raspberry/tools

# Install the rootfs
RUN mkdir -p /opt/raspberry/rootfs
ADD rootfs/lib/ /opt/raspberry/rootfs/lib
ADD rootfs/usr/ /opt/raspberry/rootfs/usr
ADD pi.cmake /opt/raspberry/