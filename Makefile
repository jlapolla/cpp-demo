CC := g++

SRCDIR := src
BUILDDIR := build
TARGETDIR := bin

SRCEXT := cpp
MAIN_SOURCES := $(shell find src -maxdepth 1 -type f -name *.$(SRCEXT))
MAIN_OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .o,$(basename $(MAIN_SOURCES))))
SOURCES := $(shell find src -mindepth 2 -type f -name *.$(SRCEXT))
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
	$(info MAIN_SOURCES = $(MAIN_SOURCES))
	$(info MAIN_OBJECTS = $(MAIN_OBJECTS))
	$(info SOURCES = $(SOURCES))
	$(info OBJECTS = $(OBJECTS))
	$(info CFLAGS = $(CFLAGS))

$(TARGETDIR)/demo: $(BUILDDIR)/demo.o $(OBJECTS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

# Automatic header file prerequisites
# See https://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html
$(BUILDDIR)/%.d: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(dir $@) \
	  && $(CC) $(CFLAGS) -MM $< 1>$@.$$$$ \
	  && sed 's,\($(notdir $(basename $@))\)\.o[ :]*,$(dir $@)\1.o $@ : ,g' 0<$@.$$$$ 1>$@ \
	  && rm -f $@.$$$$

include $(addsuffix .d,$(basename $(MAIN_OBJECTS) $(OBJECTS)))

