//
// Created by onureozcan on 04.06.2019.
//

#include <multiboot.h>
#include <display/console.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define  LOG_TAG "INIT"

void init_gather_user_programs_from_boot_modules(struct multiboot_info *multiboot_struct) {
    console_log(LOG_TAG, "getting inital user programs from boot modules\n");
}

void init_load_hello() {
    console_log(LOG_TAG, "loading hello...\n");
}