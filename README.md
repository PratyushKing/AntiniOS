# AntiniOS
<img src="https://www.aschey.tech/tokei/github/PratyushKing/AntiniOS?label=Lines%20Of%20Code&labelColor=363a4f&color=cba6f7"> <img alt="GitHub License" src="https://img.shields.io/github/license/PratyushKing/AntiniOS?label=License&colorA=363a4f&colorB=cba6f7"> ![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/PratyushKing/AntiniOS/c-cpp.yml?label=Build%20Status&colorA=363a4f&colorB=cba6f7)
<br>
AntiniOS is an OS in C++ mainly for learning purposes..

## Why?
idk, just to learn OSDev'ing

## Things done:
- Limine and x86_64 support.
- Basic general IO functions.

## Build
### Windows
Follow the steps given for linux but just use msys2, cygwin or an alternative (probably WSL) and follow.

### MacOS
- Make sure you have homebrew installed (if not google it up lol).
- Install gcc and binutils properly via homebrew. You do also need to install GNU Make which most likely is different from MacOS's make. It's pretty similar but it is suggested to use GNU Make since it is tested and also you also need to install git, xorriso (or libisoburn) and optionally QEMU that is for the x86_64 architecture (since we need to run AntiniOS in 64 bit)
- Clone this github repository.
- Run `make clean` if there is any bin folder, ensure it's a clean build. (if it shows an error that means it's already clean)
- Run `make` directly and it will compile, link and form the ISO in the bin/ folder.
- Run `make test` to run the ISO then and there (via `qemu-system-x86_64`) or if you wish to use other hypervisors like VMWare or VirtualBox, the ISO is at `bin/AntiniOS.iso`, you can use it with your preference. (QEMU is preferred however)

### Linux
- Via your distro's package manager, you have to roughly install 3 packages, `gcc` (and if not included `g++` also), `binutils` (for `as` and `ld`) and optionally the `qemu-system` package (which is to test the OS). You do also need xorriso and make but I assume you already have it, I suggest checking however since it is very important. On arch linux, you can do `sudo pacman -S gcc binutils qemu-system-x86 libisoburn make --needed --noconfirm` (x86 is required as it provides for x86_64 too and it's the emulation we need as Antini is 64 bit)
- Clone the repo through `git clone https://github.com/PratyushKing/AntiniOS` and cd inside it.
- Run `make clean` if there is a bin/ folder. (If not, it will automatically throw an error, don't worry it just means you haven't built it yet)
- Run `make` to compile the whole OS (it will link, compile and prepare the iso for you).
- Run `make test` and it will automatically launch QEMU (x86_64 version) and let you test the ISO! Or you can just use the ISO however you feel like, it is in `bin/AntiniOS.iso`
