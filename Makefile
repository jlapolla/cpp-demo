CC := g++

SRCDIR := src
BUILDDIR := build
TARGETDIR := bin

SRCEXT := cpp
SOURCES := $(shell find src -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .o,$(basename $(SOURCES))))
CFLAGS := -std=c++14 -g -Wall

.PHONY: null
null:

.DEFAULT_GOAL := null

.PHONY: clean
clean:
	rm -rf $(BUILDDIR) $(TARGETDIR)

.PHONY: object
object: $(OBJECTS)

.PHONY: printvar
printvar:
	$(info CC = $(CC))
	$(info SRCDIR = $(SRCDIR))
	$(info BUILDDIR = $(BUILDDIR))
	$(info TARGETDIR = $(TARGETDIR))
	$(info SRCEXT = $(SRCEXT))
	$(info SOURCES = $(SOURCES))
	$(info OBJECTS = $(OBJECTS))
	$(info CFLAGS = $(CFLAGS))

$(TARGETDIR)/demo: $(filter $(BUILDDIR)/demo/%,$(OBJECTS))
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

