symbol-file .build/boot/axolotl.bin
target remote | qemu-system-i386 -vga std -net nic,model=ne2k_pci -d cpu_reset -D qemu.log -serial file:syslog.log -cdrom axolotl.iso -S -gdb stdio