//
// Created by onureozcan on 29.05.2019.
//

#include <cpu/gdt.h>
#include <cpu/tss.h>

static uint64_t create_descriptor(uint32_t base, uint32_t limit, uint8_t access, uint8_t grand) {
    struct gdt_descriptor descriptor = {0};
    //! set limit and base addresses
    descriptor.baseLo	= (uint16_t)(base & 0xffff);
    descriptor.baseMid	= (uint8_t)((base >> 16) & 0xff);
    descriptor.baseHi	= (uint8_t)((base >> 24) & 0xff);
    descriptor.limit	= (uint16_t)(limit & 0xffff);

    //! set flags and grandularity bytes
    descriptor.flags = access;
    descriptor.grand = (uint8_t)((limit >> 16) & 0x0f);
    descriptor.grand |= grand & 0xf0;
//    descriptor.limit = limit;
//    descriptor.baseLo = base & 0xFFFF;
//    descriptor.baseMid = (base >> 16) & 0x000000FF;
//    descriptor.baseHi = ((base >> 24) & 0xFF);
//    descriptor.flags = flag;
//    descriptor.grand = grand;
//
//    descriptor.grand = (uint8_t) ((limit >> 16) & 0x0f);
//    descriptor.grand |= grand & 0xf0;
    return *((uint64_t *) &descriptor);
}

static uint64_t get_tss_descriptor() {
    uint32_t base = (uint32_t) &tss;
    return create_descriptor(base, base + (sizeof(struct tss_entry)),
                             I86_GDT_DESC_ACCESS | I86_GDT_DESC_EXEC_CODE | I86_GDT_DESC_DPL | I86_GDT_DESC_MEMORY,
                             0);
}

void gdt_init() {

    gdt_entries[0] = create_descriptor(0, 0, 0, 0);
    gdt_entries[1] = create_descriptor(0, 0xFFFFFFFF,
                                       I86_GDT_DESC_READWRITE | I86_GDT_DESC_EXEC_CODE | I86_GDT_DESC_CODEDATA |
                                       I86_GDT_DESC_MEMORY,
                                       I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK);
    gdt_entries[2] = create_descriptor(0, 0xFFFFFFFF,
                                       I86_GDT_DESC_READWRITE | I86_GDT_DESC_CODEDATA | I86_GDT_DESC_MEMORY,
                                       I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK);
    gdt_entries[3] = create_descriptor(0, 0xFFFFFFFF,
                                       I86_GDT_DESC_READWRITE | I86_GDT_DESC_EXEC_CODE | I86_GDT_DESC_CODEDATA |
                                       I86_GDT_DESC_MEMORY | I86_GDT_DESC_DPL,
                                       I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK);
    gdt_entries[4] = create_descriptor(0, 0xFFFFFFFF,
                                       I86_GDT_DESC_READWRITE | I86_GDT_DESC_CODEDATA | I86_GDT_DESC_MEMORY |
                                       I86_GDT_DESC_DPL,
                                       I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK);

    // install TSS descriptor
    gdt_entries[5] = get_tss_descriptor();

    set_gdtr((uint32_t) gdt_entries, GDT_ENTRIES_SIZE * sizeof(uint64_t) - 1);
    gdt_load_kernel_selectors();
    console_log(LOG_TAG, "loaded gdt at %p \n", gdt_entries);

}