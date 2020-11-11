.section .text
    .global reloadGDT
reloadGDT:
    # We pass in our descriptors from C via eax
    mov 0x4(%esp), %eax

    # Load the register
    lgdt (%eax)

    # 0x10 is where the data segment is located, load it into all of the registers
    mov $0x10, %ax
    mov %ax, %ds 
    mov %ax, %es 
    mov %ax, %fs 
    mov %ax, %gs 
    mov %ax, %ss

    # Flush the registers
    jmp $0x08, $flush
flush:
    ret
