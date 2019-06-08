//
// Created by onureozcan on 04.06.2019.
//

#ifndef ZEROOS_INIT_H
#define ZEROOS_INIT_H

/* finds location of initial programs
 * it relies on GRUB boot modules to read files.
 * pretends that it reads files but what it actually does is
 * reading boot modules and passing them off as files
 * this is the reason it needs to have a pointer to multiboot struct *
 * */
void init_gather_user_programs_from_boot_modules(struct multiboot_info *);

/**
 * loads the dead simple hello world user app
 */
void init_load_hello();

#endif //ZEROOS_INIT_H
