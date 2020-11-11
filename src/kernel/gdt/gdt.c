#include "gdt.h"

// Adapted from https://wiki.osdev.org/GDT_Tutorial
static void gdt_create_descriptor(gdt_entry_t* entry, uint32_t base, uint32_t limit, uint16_t flag) {
    // Create the high 32 bit segment
    entry->high = limit & 0x000F0000; // Set limit bits 19:16
    entry->high |= (flag <<  8) & 0x00F0FF00; // Set type, p, dpl, s, g, d/b, l and avl fields
    entry->high |= (base >> 16) & 0x000000FF; // Set base bits 23:16
    entry->high |= base & 0xFF000000; // Set base bits 31:24
 
    // Create the low 32 bit segment
    entry->low |= base  << 16; // Set base bits 15:0
    entry->low |= limit  & 0x0000FFFF; // Set limit bits 15:0
}

void gdt_table_initialize() {
    static gdt_entry_t entries[5] = {0};
    static gdt_descriptor_t descriptor = {0};

    descriptor.table_base = (uint32_t)&entries;
    descriptor.table_size = sizeof(entries) - 1;

    gdt_create_descriptor(&entries[0], 0, 0, 0);
    gdt_create_descriptor(&entries[1], 0x00000000, 0x000FFFFF, (GDT_CODE_PL0));
    gdt_create_descriptor(&entries[2], 0x00000000, 0x000FFFFF, (GDT_DATA_PL0));
    gdt_create_descriptor(&entries[3], 0x00000000, 0x000FFFFF, (GDT_CODE_PL3));
    gdt_create_descriptor(&entries[4], 0x00000000, 0x000FFFFF, (GDT_DATA_PL3));

    reloadSegmentRegisters(&descriptor);
}