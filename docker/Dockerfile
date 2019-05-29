FROM ubuntu:18.04
RUN apt-get update
RUN apt-get install -y xorriso
RUN apt-get install -y grub-common
RUN apt-get install -y nasm
RUN apt-get install -y gcc
RUN DEBIAN_FRONTEND=noninteractive apt-get --quiet --yes install -y grub-pc-bin
RUN apt-get -y install cmake