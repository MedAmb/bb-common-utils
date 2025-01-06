FROM debian:latest

# Install dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    git \
    zlib1g-dev \
    libdbus-glib-1-dev \
    build-essential \
    libfmt-dev \
    libspdlog-dev \
    clang-format \
    clang-tidy

WORKDIR /work/jj

RUN git clone  https://github.com/COVESA/dlt-daemon.git

WORKDIR /work/jj/dlt-daemon

RUN mkdir build

WORKDIR /work/jj/dlt-daemon/build

RUN cmake ..

RUN make

RUN make install

RUN ldconfig

WORKDIR /work

RUN rm -rf jj


