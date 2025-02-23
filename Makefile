# Directories
SRCDIR := src
BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj
INCLUDE := include
PREFIX := /usr/z80-elf

# Compiler and tools
CC := ez80-clang
AS := z80-elf-as
AR := z80-elf-ar

# Compiler flags
CFLAGS := -target z80 -S -nostdinc -I$(INCLUDE) --std=c90 -pedantic-errors -Os -mllvm -z80-gas-style
ASFLAGS :=
ARFLAGS := rcs

# Source files
CSRC := $(shell find $(SRCDIR) -name '*.c')
ASRC := $(shell find $(SRCDIR) -name '*.s')

# Object files
COBJ := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(CSRC))
AOBJ := $(patsubst $(SRCDIR)/%.s,$(OBJDIR)/%.o,$(ASRC))
OBJS := $(COBJ) $(AOBJ)

.PHONY: all clean

all: $(BUILDDIR)/libc.a

clean:
	rm -rf $(BUILDDIR)/*

install:
	cp $(BUILDDIR)/libc.a $(PREFIX)/lib
	cp -r $(INCLUDE)/* $(PREFIX)/include

$(BUILDDIR) $(OBJDIR):
	mkdir -p $@

$(BUILDDIR)/libc.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.s | $(OBJDIR)
	mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

# The (e)Z80 compiler doesn't assemble for us, so we need to do it ourselves
$(OBJDIR)/%.o: $(OBJDIR)/%.s
	$(AS) $(ASFLAGS) -march=ez80 -o $@ $<

$(OBJDIR)/%.s: $(SRCDIR)/%.c | $(OBJDIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $<
