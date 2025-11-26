#!/bin/bash

set -e

mkdir -p build 

arm-none-eabi-as -mcpu=cortex-m3 -mthumb src/startup.s -o build/startup.o
arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -c src/main.c -o build/main.o

arm-none-eabi-ld -T linker.ld build/startup.o build/main.o -o build/firmware.elf
arm-none-eabi-objcopy -O binary build/firmware.elf build/firmware.bin

qemu-system-arm -M lm3s6965evb -kernel build/firmware.bin -nographic
