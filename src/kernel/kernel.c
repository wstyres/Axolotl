#include "tty.h"
#include <libc/stdio/stdio.h>
#include <kernel/gdt/gdt.h>
#include <kernel/interrupts/interrupts.h>

void force_hardware_irq() {
	printf("Forcing hardware IRQ...");
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdiv-by-zero"
	int i = 500/0;
#pragma GCC diagnostic pop
	printf("%d", i);
}

void force_page_fault() {
	printf("Forcing page fault...");
	uint32_t* ptr = (uint32_t*)0xA0000000;
	uint32_t do_fault = *ptr;
	printf("This should never be reached: %d", do_fault);
}

void test_interrupts() {
	printf("Testing interrupts...");
	asm volatile("mov $0xdeadbeef, %eax");
	asm volatile("mov $0xcafebabe, %ecx");
	asm volatile("int $0x3");
	//asm volatile("int $0x4");
}

void kernel_main() {
    create_terminal();

    write("Initializing GDT Tables...\n");
    gdt_table_initialize();
    write("GDT Tables Initialized.\n");

    write("Initializing IDT Tables...\n");
    idt_table_initialize();
    write("IDT Tables Initialized.\n");

    write("Performing Tests...");
    // force_hardware_irq();
    // force_page_fault();
    // test_interrupts();
}