.section .text
    .global irq0
    .global irq1
    .global irq2
    .global irq3
    .global irq4
    .global irq5
    .global irq6
    .global irq7
    .global irq8
    .global irq9
    .global irq10
    .global irq11
    .global irq12
    .global irq13
    .global irq14
    .global irq15
    .global reloadIDT
 
irq0:
    pusha
    call irq0_handler
    popa
    iret
 
irq1:
    pusha
    call irq1_handler
    popa
    iret
 
irq2:
    pusha
    call irq2_handler
    popa
    iret
 
irq3:
    pusha
    call irq3_handler
    popa
    iret
 
irq4:
    pusha
    call irq4_handler
    popa
    iret
 
irq5:
    pusha
    call irq5_handler
    popa
    iret
 
irq6:
    pusha
    call irq6_handler
    popa
    iret
 
irq7:
    pusha
    call irq7_handler
    popa
    iret
 
irq8:
    pusha
    call irq8_handler
    popa
    iret
 
irq9:
    pusha
    call irq9_handler
    popa
    iret
 
irq10:
    pusha
    call irq10_handler
    popa
    iret
 
irq11:
    pusha
    call irq11_handler
    popa
    iret
 
irq12:
    pusha
    call irq12_handler
    popa
    iret
 
irq13:
    pusha
    call irq13_handler
    popa
    iret
 
irq14:
    pusha
    call irq14_handler
    popa
    iret
 
irq15:
    pusha
    call irq15_handler
    popa
    iret

reloadIDT:
    # We pass in our descriptors from C via eax
    mov 0x4(%esp), %eax

    # Load the register
    lidt (%eax)

    # Now that interrupts are loaded, we can enable them again
    sti

    ret
