CC := g++

SRCDIR := src
BUILDDIR := build

SRCEXT := cpp
SOURCES := $(shell find src -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .o,$(basename $(SOURCES))))
CFLAGS := -g -Wall

.PHONY: null
null:

.DEFAULT_GOAL := null

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)

.PHONY: object
object: $(OBJECTS)

.PHONY: printvar
printvar:
	$(info CC = $(CC))
	$(info SRCDIR = $(SRCDIR))
	$(info BUILDDIR = $(BUILDDIR))
	$(info SRCEXT = $(SRCEXT))
	$(info SOURCES = $(SOURCES))
	$(info OBJECTS = $(OBJECTS))
	$(info CFLAGS = $(CFLAGS))

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $(CFLAGS) $<

