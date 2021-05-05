CXX = /home/joseph/opt/cross/bin/i686-elf-g++
NASM = nasm
#LD = /home/joseph/opt/cross/bin/i686-elf-ld
LDFLAGS = -T linker.ld -o iosifos.bin -ffreestanding -nostdlib -g3
NASMFLAGS = -felf32 -g
FLAGS = -ffreestanding -nostdlib -I include -g3
INCLUDEDIR = include
SRCDIR = src
BINDIR = bin
OBJDIR = obj

TARGET = ./bin/iosifos.bin

SOURCES=$(shell find src -type f -iname '*.*')
NASMSOURCE = $(shell file src -type f -iname '*.asm')
OBJECTS = $(foreach x, $(basename $(SOURCES)), $(x).o)

all: $(TARGET)
	cp iosifos.bin isodir/boot/iosifos.bin
	grub-mkrescue -o bin/IosifOS.iso isodir
	find ./ -type f -name "*.o" -delete

$(TARGET): $(OBJECTS)
		$(CXX) -o $@ $^ $(LDFLAGS)


# You don't even need to be explicit here,
# compiling C files is handled automagically by Make.
%.o: %.cpp
		$(CXX) $(FLAGS) -c $^ -o $@

%.o: %.asm
	$(NASM) $(NASMFLAGS) -o $@ $^

clean:
	find ./ -type f -name "*.o" -delete