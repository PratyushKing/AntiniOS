COMPILER=x86_64-elf-g++
LINKER=x86_64-elf-gcc
ASSEMBLER=x86_64-elf-as
ASSEMBLER_FLAGS=-O2
COMPILER_FLAGS=\
    -Wall \
    -Wextra \
    -ffreestanding \
    -fno-stack-protector \
    -fno-stack-check \
    -fno-lto \
    -fPIE \
    -m64 \
    -march=x86-64 \
    -mno-80387 \
    -mno-mmx \
    -mno-sse \
    -mno-sse2 \
    -mno-red-zone
LINKER_FLAGS=-ffreestanding -O2 -nostdlib bin/kernel.o
BIN_LOCATION=bin/AntiniOS.bin

all: prepare kernel linker prepare-limine

prepare:
	@mkdir bin/ -p

clean: clean_bin clean_limine

clean_bin:
	@rm -fr bin/* limine_building/bin limine_building/iso # fr is a joke btw instead of rf

clean_limine:
	@rm -fr limine_building/bin limine_building/iso

kernel:
	@$(COMPILER) -c src/kernel.cpp -o bin/kernel.o $(COMPILER_FLAGS)

linker:
	@$(LINKER) -T src/linker.ld -o bin/AntiniOS.bin $(LINKER_FLAGS)

prepare-grub:
	@#mkdir -p bin/iso/boot/grub
	@#cp bin/AntiniOS.bin bin/iso/boot/
	@#cp src/grub/grub.cfg bin/iso/boot/grub/
	@#grub-mkrescue -o bin/AntiniOS.iso bin/iso/
	@echo "Grub is deprecated."

prepare-limine:
	@#echo "Before we proceed, do note that you must have git installed or limine will fail to work, Press enter to continue or Ctrl+C to exit."
	@#read
	@mkdir -p limine_building/bin/
	@git clone "https://github.com/limine-bootloader/limine.git" "limine_building/bin/" --branch=v7.x-binary --depth=1
	@cd limine_building/bin/
	@make -C limine_building/bin/
	@cd ../../
	@mkdir -p limine_building/iso/EFI/BOOT
	@mkdir -p limine_building/iso/boot/limine
	@cp $(BIN_LOCATION) limine_building/iso/boot/
	@cp limine_building/limine.cfg limine_building/bin/limine-bios.sys limine_building/bin/limine-bios-cd.bin limine_building/bin/limine-uefi-cd.bin limine_building/iso/boot/limine/
	@cp limine_building/bin/BOOTX64.EFI limine_building/bin/BOOTIA32.EFI limine_building/iso/EFI/BOOT
	@cd limine_building/iso
	@xorriso -as mkisofs -b boot/limine/limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot boot/limine/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		limine_building/iso/ -o bin/AntiniOS.iso -eltorito-platform efi
	@./limine_building/bin/limine bios-install bin/AntiniOS.iso

test:
	@qemu-system-x86_64 -cdrom bin/AntiniOS.iso -debugcon file:/dev/stdout # a lot of work left here but will add later
