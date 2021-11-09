# See LICENSE file for copyright and license details.
# Install paths
PREFIX ?= /usr/local

SRC = backlight.c
OBJ = $(SRC:.c=.o)

CFLAGS += -Wall

all: backlight

config.h:
	cp config.def.h config.h

backlight: $(OBJ)

$(OBJ): config.h

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f backlight $(DESTDIR)$(PREFIX)/bin

clean:
	rm -f backlight $(OBJ)

.PHONY: all clean install
