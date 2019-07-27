#!/usr/bin/env bash
qemu-system-x86_64 -cdrom dist/os.iso -no-reboot -d int -D ./qemu.log -enable-kvm -serial file:serial.log