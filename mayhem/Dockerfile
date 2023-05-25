FROM ubuntu:20.04

## Install build dependencies.
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y cmake build-essential libpng-dev

## Add source code to the build stage.
ADD . /zint
WORKDIR /zint

## Build
RUN mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install

## Uninstall build dependencies.
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get remove -y cmake build-essential libpng-dev

