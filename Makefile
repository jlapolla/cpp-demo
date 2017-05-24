CC := g++
SRCEXT := cpp
PROJECTDIR := src

SRCDIR_LIBDEMO := $(PROJECTDIR)/libdemo
BUILDDIR_LIBDEMO := $(SRCDIR_LIBDEMO)/obj/Release
BUILDDIR := build
TARGETDIR := bin

SOURCES := $(shell find $(SRCDIR_LIBDEMO) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR_LIBDEMO)/%,$(BUILDDIR_LIBDEMO)/%,$(addsuffix .o,$(basename $(SOURCES))))

CFLAGS := -std=c++14 -g -Wall
LIB :=

$(BUILDDIR_LIBDEMO)/%.o: $(SRCDIR_LIBDEMO)/%.$(SRCEXT)
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

# Automatic header file prerequisites
# See https://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html
$(BUILDDIR_LIBDEMO)/%.d: $(SRCDIR_LIBDEMO)/%.$(SRCEXT)
	@mkdir -p $(dir $@) \
	  && $(CC) $(CFLAGS) -MM $< 1>$@.$$$$ \
	  && sed 's,\($(notdir $(basename $@))\)\.o[ :]*,$(dir $@)\1.o $@ : ,g' 0<$@.$$$$ 1>$@ \
	  && rm -f $@.$$$$

include $(addsuffix .d,$(basename $(OBJECTS)))

MAIN_SOURCES := $(shell find $(PROJECTDIR) -maxdepth 1 -type f -name *.$(SRCEXT))
MAIN_OBJECTS := $(patsubst $(PROJECTDIR)/%,$(BUILDDIR)/%,$(addsuffix .o,$(basename $(MAIN_SOURCES))))

$(TARGETDIR)/%: $(BUILDDIR)/%.o $(OBJECTS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

$(BUILDDIR)/%.o: $(PROJECTDIR)/%.$(SRCEXT)
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

# Automatic header file prerequisites
# See https://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html
$(BUILDDIR)/%.d: $(PROJECTDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@) \
	  && $(CC) $(CFLAGS) -MM $< 1>$@.$$$$ \
	  && sed 's,\($(notdir $(basename $@))\)\.o[ :]*,$(dir $@)\1.o $@ : ,g' 0<$@.$$$$ 1>$@ \
	  && rm -f $@.$$$$

include $(addsuffix .d,$(basename $(MAIN_OBJECTS)))

PROJECTDIR_TEST := test
SRCDIR_TEST := $(PROJECTDIR_TEST)/demo
BUILDDIR_TEST := testbuild
TARGETDIR_TEST := testbin

SOURCES_TEST := $(shell find $(SRCDIR_TEST) -type f -name *.$(SRCEXT))
OBJECTS_TEST := $(patsubst $(SRCDIR_TEST)/%,$(BUILDDIR_TEST)/%,$(addsuffix .o,$(basename $(SOURCES_TEST))))

CFLAGS_TEST := $(CFLAGS) -I $(PROJECTDIR) -I /usr/include/cppunit $(shell cppunit-config --cflags)
LIB_TEST := $(LIB) $(shell cppunit-config --libs)

$(TARGETDIR_TEST)/main: $(OBJECTS) $(OBJECTS_TEST)
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

include $(addsuffix .d,$(basename $(OBJECTS_TEST)))

.PHONY: null
null:

.DEFAULT_GOAL := null

.PHONY: all
all: $(patsubst $(BUILDDIR)/%.o,$(TARGETDIR)/%,$(MAIN_OBJECTS))

.PHONY: test
test: $(TARGETDIR_TEST)/main
	$(TARGETDIR_TEST)/main

.PHONY: clean
clean:
	rm -rf $(BUILDDIR) $(dir $(BUILDDIR_LIBDEMO)) $(TARGETDIR) $(BUILDDIR_TEST) $(TARGETDIR_TEST)

.PHONY: object
object: $(OBJECTS)

.PHONY: printvar
printvar:
	$(info CC = $(CC))
	$(info PROJECTDIR = $(PROJECTDIR))
	$(info SRCDIR_LIBDEMO = $(SRCDIR_LIBDEMO))
	$(info BUILDDIR_LIBDEMO = $(BUILDDIR_LIBDEMO))
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
	$(info SOURCES_TEST = $(SOURCES_TEST))
	$(info OBJECTS_TEST = $(OBJECTS_TEST))
	$(info CFLAGS_TEST = $(CFLAGS_TEST))
	$(info LIB_TEST = $(LIB_TEST))

