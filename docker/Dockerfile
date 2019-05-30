FROM ubuntu:18.04
RUN apt-get update
RUN apt-get install -y xorriso
RUN apt-get install -y grub-common
RUN apt-get install -y nasm
RUN apt-get install -y gcc-6
RUN DEBIAN_FRONTEND=noninteractive apt-get --quiet --yes install -y grub-pc-bin
RUN apt-get -y install cmake
RUN apt-get -y install libc6-dev-i386
RUN apt-get -y install gcc-6-multilib
RUN apt-get -y install wget
RUN apt-get -y install unzip
