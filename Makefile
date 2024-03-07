# Makefile
# Version 3

CC = gcc
CFLAGS = -Wall `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
# Header4.c
HEADERS =	flashfunctionheader.h \
			flashheader.h \
			renamefunction.h \
			functionheader.h 

# update engine need
SRCS =	Header1.c \
		Header2.c \
		Header3.c \
		adbcheck.c \
		makedir.c \
		changedir.c \
		bootrecover.c \
		bootfastboot.c \
		rebootfastboot.c \
		lockunlockbootloader.c \
		erasedata.c \
		renamefilerecovery.c \
		renamefileboot.c \
		renamefilevendor.c \
		renamefilesys.c \
		renamefilevbmeta.c \
		renameGUI.c \
		flashrecovery.c \
		flashboot.c \
		flashvendor.c \
		flashvendorboot.c \
		flashsystem.c \
		flashpayload.c \
		flashvbmeta.c \
		flashGUI.c \
		info.c \
		about.c \
		GUI.c \
		
OBJS = $(SRCS:.c=.o)
TARGET = Projekt-122-l

all: $(TARGET)

$(TARGET): $(OBJS) $(HEADERS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o 


