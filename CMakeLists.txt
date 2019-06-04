cmake_minimum_required(VERSION 3.5.1)
project(ZeroOs C)
set(CMAKE_C_STANDARD 11)
enable_language(ASM_NASM)

set(CMAKE_C_FLAGS "-m32 -Wall -g")
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> -f elf32 -o <OBJECT> <SOURCE>")

include_directories(src/include)
include_directories(src/kernel/lib/include)

add_executable(kernel
        src/kernel/kernel.c
        src/kernel/kernel.asm
        src/kernel/common.asm
        src/kernel/display/console.c
        src/kernel/cpu/gdt.c
        src/kernel/cpu/idt.asm
        src/kernel/cpu/idt.c
        src/kernel/cpu/ihandlers.c
        src/kernel/cpu/ihandlers.asm
        src/kernel/cpu/gdt.asm
        src/kernel/lib/tinyprintf/tinyprintf.c
        src/kernel/memory/memory_manager.c
        src/kernel/memory/malloc.c
        src/kernel/memory/page_manager.c
        src/kernel/memory/page_manager.asm
        src/kernel/lib/str/k_string.c
        src/kernel/cpu/tss.c
        src/kernel/cpu/tss.asm
        src/kernel/cpu/usermode.asm
        src/kernel/tasking/task_manager.c
)

set_target_properties(kernel PROPERTIES LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/src/link.ld -F dwarf -g -nostdlib")
set_target_properties(kernel PROPERTIES COMPILE_FLAGS "-m32 -masm=intel -nostdlib -g -Wall")

target_link_libraries(kernel libgcc.a)

## TESTS

enable_testing()

add_executable(malloc_tester
        src/tests/mock/mock_console_functions.c
        src/kernel/memory/memory_manager.c
        src/kernel/memory/malloc.c
        src/tests/malloc_tester.c
)

add_test(test_k_malloc malloc_tester COMMAND malloc_tester)
