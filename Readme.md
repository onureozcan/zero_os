# Zero Os

It is an x86 hobby os written in C and assembly.   
Uses GRUB to boot.  
It utilizes paging, can load elf32 binaries (only statically linked).   
Has multitasking and multithreading.   
Uses newlib in user applications. 
17 syscalls required by newlib are placed in syscall interface. 
Some of them has implementations and some are empty.  
No filesystem driver and virtual file system yet.  
Uses VBE linear frame buffer but does not have a gui yet. Uses sequences of simple bezier curves for drawing fonts rather than standard formats like otf, ttf etc.

It is still too young and I am implementing core features one by one. 
As new features are added, will amend this file also.

**How to build**:

Build environment and dependencies are intended to be provided by dockerfiles. 
Host environment just needs docker for building and qemu for testing.

Before building iso image, building newlib is a must. User apps depend on it.
Therefore first run `build_newlib_using_docker.sh` inside `build_scripts` folder.
This will download newlib and build. 
The resulting libc.a will only be used to link against user apps so building newlib just once is enough as long as you do not want to change newlib version or build flags or so.

Secondly, run `build_iso_using_docker` in that folder. It builds both kernel and user apps, creates `dist/os.iso` and runs it on qemu as well.

**Running on emulator**:
 
 Building iso runs the created image also.
 if you just want to run it on a different emulator you can use this iso as well.
 
 Never run it on a real machine.
 
 **Debugging**
 
` gdb_debug_qemu.sh` starts qemu with gdb server listening on port 1234. 
 Symbol files will appear inside iso folder after build. You can configure your ide to debug user apps or kernel image.
 
 **Screenshots**
 
 (newest to oldest)
 
 ![image](https://user-images.githubusercontent.com/21360651/59981304-f0c7aa80-9609-11e9-88d9-30ec048bcee5.png)

 
 ![image](https://user-images.githubusercontent.com/21360651/59148391-25841100-8a11-11e9-98bb-dfdefec6eca3.png)

 
 