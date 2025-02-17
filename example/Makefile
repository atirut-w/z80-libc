# Directories
SRCDIR := src
BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj
PREFIX := /usr/z80-elf

# Compiler and tools
CC := ez80-clang
AS := z80-elf-as
LD := z80-elf-ld
OBJCOPY := z80-elf-objcopy

# Compiler flags
CFLAGS := -target z80 -S -nostdinc -I$(PREFIX)/include --std=c90 -pedantic-errors -O0 -mllvm -z80-gas-style
LDFLAGS := -T linker.ld
LDLIBS := -L$(PREFIX)/lib -lc

# Source files
CSRC := $(wildcard $(SRCDIR)/*.c)
ASRC := $(wildcard $(SRCDIR)/*.s)

# Object files
COBJ := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(CSRC))
AOBJ := $(patsubst $(SRCDIR)/%.s,$(OBJDIR)/%.o,$(ASRC))
OBJS := $(COBJ) $(AOBJ)

.PHONY: all clean

all: $(BUILDDIR)/EXAMPLE.COM

clean:
	rm -rf $(BUILDDIR)/*

install:
	cp $(BUILDDIR)/libc.a $(PREFIX)/lib
	cp $(INCLUDE)/* $(PREFIX)/include

$(BUILDDIR) $(OBJDIR):
	mkdir -p $@

$(BUILDDIR)/EXAMPLE.COM: $(BUILDDIR)/EXAMPLE.ELF
	$(OBJCOPY) -O binary $< $@

$(BUILDDIR)/EXAMPLE.ELF: $(OBJS) | $(BUILDDIR)
	$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.s | $(OBJDIR)
	$(AS) $(ASFLAGS) -o $@ $<

# The (e)Z80 compiler doesn't assemble for us, so we need to do it ourselves
$(OBJDIR)/%.o: $(OBJDIR)/%.s
	$(AS) $(ASFLAGS) -march=ez80 -o $@ $<

$(OBJDIR)/%.s: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $<
