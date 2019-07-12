//
// Created by onureozcan on 29.06.2019.
//

/**
 * This file defines an interface of device file system.
 * Device file system maps devices to file system and will redirect read write requests to them.
 */

#ifndef ZEROOS_DEV_FS_H
#define ZEROOS_DEV_FS_H

#define DEV_FS_MOUNT_POINT "/dev"

void dev_fs_init();

#endif //ZEROOS_BOOT_FS_H
