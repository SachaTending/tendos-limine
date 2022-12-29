# Define tools
override CC=gcc
override LD=ld
override AS=nasm

# Define options

override CCFLAGS+=       \
    -std=c11             \
    -ffreestanding       \
    -fno-stack-protector \
    -fno-stack-check     \
    -fno-lto             \
    -fno-pie             \
    -fno-pic             \
    -m64                 \
    -march=x86-64        \
    -mabi=sysv           \
    -mno-80387           \
    -mno-mmx             \
    -mno-sse             \
    -mno-sse2            \
    -mno-red-zone        \
    -mcmodel=kernel      \
    -MMD                 \
    -I include			 \
	-g

override LDFLAGS +=         \
    -nostdlib               \
    -static                 \
    -m elf_x86_64           \
    -z max-page-size=0x1000 \
    -T kernel/link.ld

ifeq ($(shell $(LD) --help 2>&1 | grep 'no-pie' >/dev/null 2>&1; echo $$?),0)
    override LDFLAGS += -no-pie
endif

override NASMFLAGS += \
    -f elf64

override QEMU = qemu-system-x86_64

override HEADER_DEPS := $(FILES:.c=.d)

KERNEL = out.kern

# Here is includes

include target/*.target

# Build targets

build: kern

kern: $(FILES)
	@echo LD $(KERNEL)
	@$(LD) $(FILES) $(LDFLAGS) -o out.kern

-include $(HEADER_DEPS)

%.o: %.c
	@echo CC $@
	@$(CC) $(CCFLAGS) $(CFLAGS) -c $< -o $@

%.o: %.S
	@echo AS $@
	@$(CC) $(CCFLAGS) $(CFLAGS) -c $< -o $@

%.o: %.asm
	@echo NASM $@
	@$(AS) $(NASMFLAGS) $< -o $@

run: iso
	@echo QEMU -cdrom image.iso
	@$(QEMU) -cdrom image.iso -serial stdio -m 512m

.PHONY: clean cleanw

clean:
	@echo RM $(FILES) out.kern image.iso
	@rm $(FILES) out.kern image.iso -f

cleanw:
	@echo DEL $(FILES) out.kern image.iso
	@del $(FILES) out.kern image.iso

iso: build
	@echo CP limine/out.kern
	@echo XORRISO image.iso
	@cp out.kern limine/
	@xorriso -as mkisofs -b limine-cd.bin \
	    -no-emul-boot -boot-load-size 4 -boot-info-table \
	    --efi-boot limine-cd-efi.bin \
	    -efi-boot-part --efi-boot-image --protective-msdos-label \
	    limine -o image.iso