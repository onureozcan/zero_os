#!/usr/bin/env bash
mkdir -p ../newlib; # makes ignored directory
cd ../docker/build_newlib_env && docker-compose build && docker-compose up