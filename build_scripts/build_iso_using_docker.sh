#!/usr/bin/env bash
mkdir -p ../dist; # makes ignored directory
cd ../docker/build_iso_env && docker-compose build && docker-compose up && cd ../.. && ./run_qemu.sh