COMPILER=i686-elf-g++
LINKER=i686-elf-gcc
ASSEMBLER=i686-elf-as
ASSEMBLER_FLAGS=-O2
COMPILER_FLAGS=-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
LINKER_FLAGS=-ffreestanding -O2 -nostdlib bin/boot.o bin/kernel.o -lgcc
BIN_LOCATION=bin/AntiniOS.bin

all: boot kernel linker prepare-grub

clean:
	rm -r bin/*

boot: src/boot.s
	$(ASSEMBLER) src/boot.s -o bin/boot.o $(ASSEMBLER_FLAGS)

kernel:
	$(COMPILER) -c src/kernel.cpp -o bin/kernel.o $(COMPILER_FLAGS)

linker:
	$(LINKER) -T src/linker.ld -o bin/AntiniOS.bin $(LINKER_FLAGS)

prepare-grub:
	mkdir -p bin/iso/boot/grub
	cp bin/AntiniOS.bin bin/iso/boot/
	cp src/grub/grub.cfg bin/iso/boot/grub/
	grub-mkrescue -o bin/AntiniOS.iso bin/iso/

test:
	qemu-system-i386 bin/AntiniOS.iso -debugcon file:/dev/stdout # a lot of work left here but will add later
