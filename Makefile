BUILD_DIR = .build
SRC_DIR = src
RESOURCE_DIR = resources

AS = nasm
LD = i686-elf-ld
CC = i686-elf-gcc
SYSROOT = sysroot/
CFLAGS = -g -ffreestanding -std=gnu99 -Wall -Wextra -I./src
LDFLAGS = -ffreestanding -nostdlib -lgcc -T $(RESOURCE_DIR)/linker.ld -I./src

OBJS = src/kernel/boot.o src/kernel/kernel.o src/kernel/tty.o src/kernel/crti.o src/kernel/crtbegin.o src/kernel/crtn.o src/kernel/crtend.o src/stdlib/string/strlen.o src/stdlib/string/strcmp.o src/stdlib/stdio/printf.o src/stdlib/sys/inb.o src/stdlib/sys/outb.o src/stdlib/stdio/putchar.o src/shell/shell.o src/stdlib/malloc.o src/drivers/kb.o src/stdlib/string/strcat.o src/kernel/clock.o src/stdlib/string/itoa.c src/kernel/desc_tables.o src/kernel/interrupts.o src/kernel/isr.o src/stdlib/string/memset.o

all: $(BUILD_DIR)/boot/axolotl.bin

$(BUILD_DIR)/boot/axolotl.bin: $(OBJS)
	@mkdir -p `dirname $@`
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

src/kernel/crtbegin.o src/kernel/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.s.o:
	$(AS) -felf32 $< -o $@

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/boot/grub/grub.cfg: $(RESOURCE_DIR)/grub.cfg
	@mkdir -p `dirname $@`
	cp $^ $@

axolotl.iso: $(BUILD_DIR)/boot/axolotl.bin $(BUILD_DIR)/boot/grub/grub.cfg 
	grub-mkrescue -o $@ $(BUILD_DIR)

run: axolotl.iso
	qemu-system-i386 -vga std -net nic,model=ne2k_pci -D qemu.log -serial file:syslog.log -monitor stdio -d guest_errors -cdrom $^ 

debug: axolotl.iso
	gdb -x script.gdb

clean:
	@rm -rf src/*/*.o src/*/*.d src/*/*/*.o src/*/*/*.d src/axolotl.bin axolotl.iso *.log
