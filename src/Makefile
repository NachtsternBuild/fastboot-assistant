# Makefile
#
# (C) Copyright 2025 @NachtsternBuild
#
# License: GNU GENERAL PUBLIC LICENSE Version 3
#
# Main makefile for the UI base
# Note: modify this to use this as your main makefile

# include the language makefile
include Dependencies.mk
include language.mk

.DEFAULT_GOAL := all

# compiler
#CC = gcc # for launchpad
CC = ccache gcc
# pass on to GCC where to search
INCLUDES = -I. -Iinclude -Ibuild
# compiler config
PKG_CFLAGS = $(shell pkg-config --cflags glib-2.0 gtk4 libadwaita-1 gobject-2.0 libsecret-1 vte-2.91-gtk4 libnotify)
# linker config
PKG_LIBS = $(shell pkg-config --libs glib-2.0 gtk4 libadwaita-1 gobject-2.0 libsecret-1 vte-2.91-gtk4 libnotify)

# compiler flags
CFLAGS = -Wall -fPIC $(PKG_CFLAGS) $(INCLUDES) -pthread
# linker flags
LIBS = $(PKG_LIBS)

# all .c files
HEADERS = $(shell find . -name '*.h')
SRC = $(shell find . -name '*.c')
OBJ_CLEAN = $(shell find . -name '*.o')

# objectfiles
OBJS = $(SRC:.c=.o)

.PHONY: all objects clean po


# target
TARGET = fastboot-assistant

# standard target
all: $(TARGET) po

# create the target
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

# create the object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# running language makefile
po: lang

# cleanup
clean:
	rm -f $(OBJS)
	rm -rf locale
	rm -f $(POTFILE)
	@for lang in $(LINGUAS); do \
		rm -f $(LOCALEDIR)/$$lang/LC_MESSAGES/$(PACKAGE).mo; \
		rm -rf $(LOCALEDIR)/$$lang; \
	done
