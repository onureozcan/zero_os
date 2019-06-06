#!/usr/bin/env bash
cd ../docker/build_iso_env && docker-compose build && docker-compose up && cd ../.. && ./run_qemu.sh