BUILD_DIR = .build
SRC_DIR = src
RESOURCE_DIR = resources

AS = i686-elf-as
LD = i686-elf-ld
CC = i686-elf-gcc
SYSROOT = sysroot/
CFLAGS = -g -ffreestanding -std=gnu99 -Wall -Wextra -I./src
LDFLAGS = -nostdlib -lgcc -T $(RESOURCE_DIR)/linker.ld

OBJS = src/kernel/boot.o src/kernel/kernel.o src/kernel/tty.o src/kernel/crti.o src/kernel/crtbegin.o src/kernel/crtn.o src/kernel/crtend.o src/libc/string/strlen.o src/libc/stdio/printf.o src/libc/stdio/putchar.o

all: $(BUILD_DIR)/boot/axolotl.bin

$(BUILD_DIR)/boot/axolotl.bin: $(OBJS)
	@mkdir -p `dirname $@`
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

src/kernel/crtbegin.o src/kernel/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.s.o:
	$(AS) $< -o $@

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/boot/grub/grub.cfg: $(RESOURCE_DIR)/grub.cfg
	@mkdir -p `dirname $@`
	cp $^ $@

axolotl.iso: $(BUILD_DIR)/boot/axolotl.bin $(BUILD_DIR)/boot/grub/grub.cfg 
	grub-mkrescue -o $@ $(BUILD_DIR)

run: axolotl.iso
	qemu-system-i386 -cdrom $^

clean:
	@rm -rf src/*/*.o src/*/*.d src/axolotl.bin axolotl.iso
