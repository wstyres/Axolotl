.section .text
    .global reloadSegmentRegisters
reloadSegmentRegisters:
    # We pass in our descriptors from C via eax
    mov %eax, 4(%esp)

    # Load the register
    lgdt (%eax)

    # 0x10 is where the data segment is located, load it into all of the registers
    mov %ax, 0x10
    mov %ds, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax
    mov %ss, %ax
    ret
