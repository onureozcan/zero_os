cmake_minimum_required(VERSION 3.5.1)
project(ZeroOs C)
set(CMAKE_C_STANDARD 11)
enable_language(ASM_NASM)

set(CMAKE_C_FLAGS "-m32 -Wall -g")
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> -f elf32 -o <OBJECT> <SOURCE>")

include_directories(src/include)
include_directories(src/kernel/lib/include)
include_directories(src/common_lib/include)

add_library(canvas src/common_lib/canvas/canvas.c src/common_lib/canvas/font_data.c)
set_target_properties(canvas PROPERTIES COMPILE_FLAGS "-fno-stack-protector")

add_executable(kernel
        src/kernel/kernel.c
        src/kernel/kernel.asm
        src/kernel/common.asm
        src/kernel/display/console.c
        src/kernel/display/lfb/lfb.c
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
        src/kernel/tasking/task_manager.asm
        src/kernel/tasking/init.c src/kernel/tasking/syscall.c src/include/tasking/syscall.h)

set_target_properties(kernel PROPERTIES LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/src/link.ld -F dwarf -g -nostdlib")
set_target_properties(kernel PROPERTIES COMPILE_FLAGS "-m32 -masm=intel -nostdlib -g -Wall")

target_link_libraries(kernel libgcc.a canvas)

## TESTS

enable_testing()

add_executable(malloc_tester
        src/tests/mock/mock_console_functions.c
        src/kernel/memory/memory_manager.c
        src/kernel/memory/malloc.c
        src/tests/malloc_tester.c
        )

add_test(test_k_malloc malloc_tester COMMAND malloc_tester)

# USER PROGRAMS

set(NEWLIB_INCLUDE_DIR "../newlib/usr/i686-zero_os/include")
set(NEWLIB_LIB_DIR "../newlib/usr/i686-zero_os/lib")

add_library(syscalls_wrapper
        src/user/userlib/syscalls.c
        src/user/userlib/crt0.asm
        )

set_target_properties(syscalls_wrapper PROPERTIES COMPILE_FLAGS "-fno-stack-protector -I${NEWLIB_INCLUDE_DIR}")

add_executable(hello_world
        src/user/hello_world/hello.c
        )

set_target_properties(hello_world PROPERTIES LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/src/user/link.ld -nostdlib  -L ${NEWLIB_LIB_DIR} -lc -lm")
set_target_properties(hello_world PROPERTIES COMPILE_FLAGS "-m32 -g -I${NEWLIB_INCLUDE_DIR} -nostdlib -Wall")

target_link_libraries(hello_world PUBLIC libc.a syscalls_wrapper)






