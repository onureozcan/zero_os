#!/usr/bin/env bash
cd ../build_dir && \
rm -f CMakeCache.txt && \
cmake .. && \
make
make test
