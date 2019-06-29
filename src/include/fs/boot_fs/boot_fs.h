//
// Created by onureozcan on 29.06.2019.
//

/**
 * BootFs contains resources needed during boot time.
 * Uses grub modules to find them.
 * Mount point is /boot
 */

#ifndef ZEROOS_BOOT_FS_H
#define ZEROOS_BOOT_FS_H

#define BOOT_FS_MOUNT_POINT "/boot"

void boot_fs_init();

#endif //ZEROOS_BOOT_FS_H
