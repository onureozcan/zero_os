# Zero Os

It is an hobby os that literally has no features apart from booting up and even that is possible thanks to GRUB.
As new features are added, will update this file also.

**How to build**:

Inside build_scripts folder, there is a script named build_iso_using_docker.sh to build bootable iso images using docker. Just run it.
It will create an evironment inside a container suitable for building the image and run build.sh inside that container resulting in creation of os.iso inside dist folder.

**Running in emulator**:

 Run ./run_qemu.sh. If you want to test it in a different emulator, iso image located at dist/os.iso is bootable. You can use it.
 
 Never test it on a real machine.
 