cmake_minimum_required(VERSION 3.5.1)
project(ZeroOs C)
set(CMAKE_C_STANDARD 11)
enable_language(ASM_NASM)

set(OPTIMIZATION_FLAG "-O2")
set(DEBUG_FLAG "-g")
set(CMAKE_C_FLAGS "-m32 -Wall ${DEBUG_FLAG}")
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> -f elf32 -o <OBJECT> <SOURCE>")

include_directories(src/include)
include_directories(src/kernel/lib/include)
include_directories(src/common_lib/include)


add_library(common
        src/common_lib/canvas/canvas.c
        src/common_lib/canvas/font_data.c
        src/common_lib/util/img_utils.c
        )
set_target_properties(common PROPERTIES COMPILE_FLAGS "-fno-stack-protector ${OPTIMIZATION_FLAG}")

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
        src/kernel/tasking/init.c src/kernel/tasking/syscall.c
        src/kernel/device/device.c
        src/kernel/device/null/null.c
        src/kernel/device/framebuffer/framebuffer.c
        src/kernel/fs/volume/null/null.c
        src/kernel/fs/vfs.c
        src/kernel/fs/root_fs/root_fs.c
        src/kernel/fs/boot_fs/boot_fs.c
        src/kernel/fs/dev_fs/dev_fs.c
        src/kernel/event/event.c
        src/kernel/keyboard/keyboard.c
        src/kernel/device/mouse/mouse.c)

set_target_properties(kernel PROPERTIES LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/src/link.ld -F dwarf ${DEBUG_FLAG} -nostdlib")
set_target_properties(kernel PROPERTIES COMPILE_FLAGS "-m32 -masm=intel ${OPTIMIZATION_FLAG} -nostdlib ${DEBUG_FLAG} -Wall")

target_link_libraries(kernel libgcc.a common)

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

set_target_properties(syscalls_wrapper PROPERTIES COMPILE_FLAGS "-fno-stack-protector -I${NEWLIB_INCLUDE_DIR} ${OPTIMIZATION_FLAG}")

add_executable(hello_world
        src/user/hello_world/hello.c
        )

set_target_properties(hello_world PROPERTIES LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/src/user/link.ld -nostdlib  -L ${NEWLIB_LIB_DIR} -lc -lm")
set_target_properties(hello_world PROPERTIES COMPILE_FLAGS "-m32 ${DEBUG_FLAG} -I${NEWLIB_INCLUDE_DIR} -nostdlib -Wall")

target_link_libraries(hello_world PUBLIC libc.a syscalls_wrapper)

add_executable(window_manager
        src/user/window_manager/src/window_manager.c
        src/user/window_manager/src/screen_object.c
        src/user/window_manager/src/screen_objects/background_object.c
        src/user/window_manager/src/screen_objects/mouse_object.c
        )
set_target_properties(window_manager PROPERTIES LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/src/user/link.ld -nostdlib  -L ${NEWLIB_LIB_DIR} -lc -lm")
set_target_properties(window_manager PROPERTIES COMPILE_FLAGS "-m32 ${DEBUG_FLAG} ${OPTIMIZATION_FLAG} -I${NEWLIB_INCLUDE_DIR} -nostdlib -Wall")

target_include_directories(window_manager PRIVATE src/user/window_manager/include)
target_link_libraries(window_manager PUBLIC libc.a syscalls_wrapper common)





