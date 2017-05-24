CC := g++
SRCEXT := cpp
PROJECTDIR := src

SRCDIR := src
BUILDDIR := build
TARGETDIR := bin

MAIN_SOURCES := $(shell find $(SRCDIR) -maxdepth 1 -type f -name *.$(SRCEXT))
MAIN_OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .o,$(basename $(MAIN_SOURCES))))
SOURCES := $(shell find $(SRCDIR) -mindepth 2 -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .o,$(basename $(SOURCES))))

CFLAGS := -std=c++14 -g -Wall
LIB :=

$(TARGETDIR)/%: $(BUILDDIR)/%.o $(OBJECTS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

# Automatic header file prerequisites
# See https://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html
$(BUILDDIR)/%.d: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@) \
	  && $(CC) $(CFLAGS) -MM $< 1>$@.$$$$ \
	  && sed 's,\($(notdir $(basename $@))\)\.o[ :]*,$(dir $@)\1.o $@ : ,g' 0<$@.$$$$ 1>$@ \
	  && rm -f $@.$$$$

include $(addsuffix .d,$(basename $(MAIN_OBJECTS) $(OBJECTS)))

SRCDIR_TEST := test
BUILDDIR_TEST := testbuild
TARGETDIR_TEST := testbin

MAIN_SOURCES_TEST := $(shell find $(SRCDIR_TEST) -maxdepth 1 -type f -name *.$(SRCEXT))
MAIN_OBJECTS_TEST := $(patsubst $(SRCDIR_TEST)/%,$(BUILDDIR_TEST)/%,$(addsuffix .o,$(basename $(MAIN_SOURCES_TEST))))
SOURCES_TEST := $(shell find $(SRCDIR_TEST) -mindepth 2 -type f -name *.$(SRCEXT))
OBJECTS_TEST := $(patsubst $(SRCDIR_TEST)/%,$(BUILDDIR_TEST)/%,$(addsuffix .o,$(basename $(SOURCES_TEST))))

CFLAGS_TEST := $(CFLAGS) -I $(PROJECTDIR) -I /usr/include/cppunit $(shell cppunit-config --cflags)
LIB_TEST := $(LIB) $(shell cppunit-config --libs)

.PHONY: null
null:

.DEFAULT_GOAL := null

.PHONY: all
all: $(patsubst $(BUILDDIR)/%.o,$(TARGETDIR)/%,$(MAIN_OBJECTS))

.PHONY: test
test: $(patsubst $(BUILDDIR_TEST)/%.o,$(TARGETDIR_TEST)/%,$(MAIN_OBJECTS_TEST))
	$(TARGETDIR_TEST)/unittest

.PHONY: clean
clean:
	rm -rf $(BUILDDIR) $(TARGETDIR) $(BUILDDIR_TEST) $(TARGETDIR_TEST)

.PHONY: object
object: $(OBJECTS)

.PHONY: printvar
printvar:
	$(info CC = $(CC))
	$(info PROJECTDIR = $(PROJECTDIR))
	$(info SRCDIR = $(SRCDIR))
	$(info BUILDDIR = $(BUILDDIR))
	$(info TARGETDIR = $(TARGETDIR))
	$(info SRCEXT = $(SRCEXT))
	$(info MAIN_SOURCES = $(MAIN_SOURCES))
	$(info MAIN_OBJECTS = $(MAIN_OBJECTS))
	$(info SOURCES = $(SOURCES))
	$(info OBJECTS = $(OBJECTS))
	$(info CFLAGS = $(CFLAGS))
	$(info LIB = $(LIB))
	$(info SRCDIR_TEST = $(SRCDIR_TEST))
	$(info BUILDDIR_TEST = $(BUILDDIR_TEST))
	$(info TARGETDIR_TEST = $(TARGETDIR_TEST))
	$(info MAIN_SOURCES_TEST = $(MAIN_SOURCES_TEST))
	$(info MAIN_OBJECTS_TEST = $(MAIN_OBJECTS_TEST))
	$(info SOURCES_TEST = $(SOURCES_TEST))
	$(info OBJECTS_TEST = $(OBJECTS_TEST))
	$(info CFLAGS_TEST = $(CFLAGS_TEST))
	$(info LIB_TEST = $(LIB_TEST))

$(TARGETDIR_TEST)/%: $(BUILDDIR_TEST)/%.o $(OBJECTS) $(OBJECTS_TEST)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS_TEST) -o $@ $^ $(LIB_TEST)

$(BUILDDIR_TEST)/%.o: $(SRCDIR_TEST)/%.$(SRCEXT)
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS_TEST) -o $@ $<

# Automatic header file prerequisites
# See https://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html
$(BUILDDIR_TEST)/%.d: $(SRCDIR_TEST)/%.$(SRCEXT)
	@mkdir -p $(dir $@) \
	  && $(CC) $(CFLAGS_TEST) -MM $< 1>$@.$$$$ \
	  && sed 's,\($(notdir $(basename $@))\)\.o[ :]*,$(dir $@)\1.o $@ : ,g' 0<$@.$$$$ 1>$@ \
	  && rm -f $@.$$$$

include $(addsuffix .d,$(basename $(MAIN_OBJECTS_TEST) $(OBJECTS_TEST)))

