#!/usr/bin/env bash
./cmake_build.sh \
&& cd ../build_dir \
&& cp kernel ../iso/boot \
&& grub-mkrescue -o ../dist/os.iso ../iso \
&& chmod 777 ../dist/os.iso \
&& cd ../iso/boot \
&& objcopy --only-keep-debug kernel kernel.sym \
&& objcopy --strip-debug kernel