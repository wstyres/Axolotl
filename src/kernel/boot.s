# Constants
.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1BADB002 # Magic number for multiboot1 compliant kernel
.set CHECKSUM, -(MAGIC + FLAGS)

# Multiboot header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Fixed size 16K stack
.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    # Disable interrupts
    cli

    # Set up a simple stack
    mov $stack_top, %esp

    # Enter the kernel
    call kernel_main

    # Enter infinite loop if kernel is exited
    cli
1:  hlt
    jmp 1b

# Set the size of the _start symbol
.size _start, . - _start
