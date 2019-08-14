# Zero Os

 - It is an x86 hobby os written in C and assembly.   
 - Uses GRUB to boot.   
 - Supports PS2 mouse and keyboard.  
 - It utilizes paging, can load elf32 binaries (only statically linked).   
 - Has multitasking and multithreading.   
 - Uses newlib in user applications. 
 - 17 syscalls required by newlib are placed in syscall interface. 
 - Some of them has implementations and some are empty.  
 - Virtual file system is implemented and supports mount point lists.  
 - However no known filesystems are implemented, only an imaginary file system called boot fs for reading files from GRUB kernel modules exists.   
 - Uses VBE linear frame buffer with only 32 bit rgba modes. Gui is under construction. 
 - Mouse data and framebuffer is mapped to virtual file system at /dev/fb0 and /dev/mouse.  
 - Uses sequences of simple bezier curves for drawing fonts rather than standard formats like otf, ttf etc.

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

build ... using docker files are bash scripts but they do nothing fancy apart from triggering docker builds so that converting them to windows equivalents should be easy.

**Running on emulator**:
 
 Building iso runs the created image also.
 if you just want to run it on a different emulator you can use this iso as well.
 
 Never run it on a real machine.
 
 **Debugging**
 
` gdb_debug_qemu.sh` starts qemu with gdb server listening on port 1234. 
 Symbol files will appear inside iso folder after build. You can configure your ide to debug user apps or kernel image.
 
 **Screenshots**

 
 (14.08.2019) window manager is loaded as a user app and mouse cursor working  
 ![image](https://user-images.githubusercontent.com/21360651/63044895-dc03e680-bed7-11e9-8abd-9df40fc341a8.png) 
  
 (30.06.2019) use app reads a file via syscall  
 ![image](https://user-images.githubusercontent.com/21360651/60397265-9e2f4680-9b53-11e9-9a9f-15ce2c7620ff.png) 
 
 (06.06.2019) can load user programs and syscall interface working   
 ![image](https://user-images.githubusercontent.com/21360651/59148391-25841100-8a11-11e9-98bb-dfdefec6eca3.png)
 
 
 