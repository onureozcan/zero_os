# Zero Os

It is an x86 hobby os written in C and assembly. Uses GRUB to boot.
It utilizes paging, can load elf32 binaries (only statically linked). 
Has multitasking and multithreading but libc and syscalls are yet to come so user apps are pretty much useless :)
It still does not even have a file system, relies on GRUB boot modules to read files from iso.

It is still too young and I am implementing core features one by one. 
As new features are added, will amend this file also.

**How to build**:

Inside build_scripts folder, there is a script named build_iso_using_docker.sh to build bootable iso images using docker. Just run it.
It will create an evironment inside a container suitable for building the image and run build.sh inside that container resulting in creation of os.iso inside dist folder.

**Running in emulator**:

 Run ./run_qemu.sh. If you want to test it in a different emulator, iso image located at dist/os.iso is bootable. You can use it.
 
 Never test it on a real machine.
 