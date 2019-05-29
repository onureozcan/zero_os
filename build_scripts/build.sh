#!/usr/bin/env bash
./cmake_build.sh \
&& cd ../build_dir \
&& mv kernel ../iso/boot \
&& grub-mkrescue -o os.iso ../iso && chmod 777 os.iso
