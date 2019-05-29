cmake_minimum_required(VERSION 3.5.1)
project(ZeroOs C)
set(CMAKE_C_STANDARD 11)
enable_language(ASM_NASM)

set(CMAKE_C_FLAGS "-m32 -nostdlib -g")
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <FLAGS> -f elf32 -o <OBJECT> <SOURCE>")
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_SOURCE_DIR}/src/link.ld -F dwarf -g")

include_directories(src/include)
add_executable(kernel
        src/kernel/kernel.c
        src/kernel/kernel.asm
        src/kernel/display/console.c
)

