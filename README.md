# AntiniOS
AntiniOS is an OS in C++ mainly for learning purposes..

## Why?
idk, just to learn OSDev'ing

## Build
### Windows
Follow the steps given for linux but just use msys2, cygwin or an alternative and follow.

### MacOS
- Goto the [OSDev Cross-compiler wiki](https://wiki.osdev.org/GCC_Cross-Compiler#macOS_Users) for MacOS and then follow the steps from there to the build below on how to build a cross-compiler, make sure it includes gcc and g++. It should also be built for i686 architecture.
- Add it to the path as it says on the wiki. Make sure it works by checking `i686-elf-gcc`.
- Clone the repo through `git clone https://github.com/PratyushKing/AntiniOS` and cd inside it.
- Please check and install the following: `make`, `xorriso` (or `libisoburn`), `qemu-system-i386` and `grub` (check if `grub-mkrescue` installs because that's what we need!) [qemu is optional but it's preferred]
- Run `make clean` if there is any bin folder, ensure it's a clean build.
- Run `make` directly and it will compile, link and form the ISO in the bin/ folder
- Run `make test` to run the ISO then and there (via `qemu-system-i386`) or if you wish to use other hypervisors like VMWare or VirtualBox, the ISO is at `bin/AntiniOS.iso`, you can use it with your preference.

### Linux
- Since the OSDev wiki insists on using linux as primary, you can directly follow instructions on the [cross-compiler page](https://wiki.osdev.org/GCC_Cross-Compiler) to install the cross-compiler, by default it will build the `i686` cross-compiler we need! You need to just get the source code for binutils and gcc, configure them with how it's said in the wiki and compile them. Lastly, add them to path and check if `i686-elf-gcc` works, if it does proceed!
- Clone the repo through `git clone https://github.com/PratyushKing/AntiniOS` and cd inside it.
- Please install the following packages via your distro's package manager: `make`, `xorriso` (or `libisoburn`), `qemu-system-i386` and `grub` (check if `grub-mkrescue` installs because that's what we need!)
- Run `make clean` if there is a bin/ folder.
- Run `make` to compile the whole OS (it will link, compile and prepare the iso for you).
- Run `make test` and it will automatically launch QEMU (i386 version) and let you test the ISO! Or you can just use the ISO however you feel like, it is in `bin/AntiniOS.iso`