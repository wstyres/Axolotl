#include "interrupts.h"
#include <kernel/gdt/gdt.h>
#include <libc/stdio/stdio.h>
#include <libc/outb.h>

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void idt_set_descriptor(idt_entry_t* entry, uint32_t base, uint16_t sel, uint8_t flags) {
    entry->offset_lowerbits = base & 0xFFFF;
    entry->offset_higherbits = (base >> 16) & 0xFFFF;
    entry->selector = sel;
    entry->zero = 0;
    entry->flags = flags;
}

void idt_table_initialize() {
    static idt_entry_t entries[256] = {0};
    static idt_descriptor_t descriptor = {0};

    descriptor.table_base = (uint32_t)&entries;
    descriptor.table_size = sizeof(entries) - 1;

    idt_set_descriptor(&entries[IRQ0], (uint32_t)irq0, 0x08, 0x8E);
    idt_set_descriptor(&entries[IRQ1], (uint32_t)irq1, 0x08, 0x8E);
    idt_set_descriptor(&entries[IRQ2], (uint32_t)irq2, 0x08, 0x8E);
    idt_set_descriptor(&entries[IRQ3], (uint32_t)irq3, 0x08, 0x8E);
    idt_set_descriptor(&entries[IRQ4], (uint32_t)irq4, 0x08, 0x8E);
    idt_set_descriptor(&entries[IRQ5], (uint32_t)irq5, 0x08, 0x8E);
    idt_set_descriptor(&entries[IRQ6], (uint32_t)irq6, 0x08, 0x8E);
    idt_set_descriptor(&entries[IRQ7], (uint32_t)irq7, 0x08, 0x8E);
    idt_set_descriptor(&entries[IRQ8], (uint32_t)irq8, 0x08, 0x8E);
    idt_set_descriptor(&entries[IRQ9], (uint32_t)irq9, 0x08, 0x8E);
    idt_set_descriptor(&entries[IRQ10], (uint32_t)irq10, 0x08, 0x8E);
    idt_set_descriptor(&entries[IRQ11], (uint32_t)irq11, 0x08, 0x8E);
    idt_set_descriptor(&entries[IRQ12], (uint32_t)irq12, 0x08, 0x8E);
    idt_set_descriptor(&entries[IRQ13], (uint32_t)irq13, 0x08, 0x8E);
    idt_set_descriptor(&entries[IRQ14], (uint32_t)irq14, 0x08, 0x8E);
    idt_set_descriptor(&entries[IRQ15], (uint32_t)irq15, 0x08, 0x8E);

    reloadIDT(&descriptor);
}

void irq0_handler() {
    printf("Keyboard!\n");
    outb(0x20, 0x20); //EOI
}
 
void irq1_handler() {
    printf("Keyboard!\n");
	outb(0x20, 0x20); //EOI
}
 
void irq2_handler() {
    printf("Keyboard!\n");
    outb(0x20, 0x20); //EOI
}
 
void irq3_handler() {
    printf("Keyboard!\n");
    outb(0x20, 0x20); //EOI
}
 
void irq4_handler() {
    outb(0x20, 0x20); //EOI
}
 
void irq5_handler() {
    outb(0x20, 0x20); //EOI
}
 
void irq6_handler() {
    outb(0x20, 0x20); //EOI
}
 
void irq7_handler() {
    outb(0x20, 0x20); //EOI
}
 
void irq8_handler() {
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI          
}
 
void irq9_handler() {
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}
 
void irq10_handler() {
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}
 
void irq11_handler() {
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}
 
void irq12_handler() {
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}
 
void irq13_handler() {
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}
 
void irq14_handler() {
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}
 
void irq15_handler() {
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}