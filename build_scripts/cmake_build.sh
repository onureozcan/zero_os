#!/usr/bin/env bash
cd ../build_dir && \
rm -f CMakeCache.txt && \
rm -f ../dist/os.iso && \
cmake .. && \
make && \
make test