# See LICENSE file for copyright and license details.
# Install paths
PREFIX ?= /usr/local
MANPREFIX ?= $(PREFIX)/share/man

VERSION = 0.0.0

SRC = backlight.c
OBJ = $(SRC:.c=.o)

CFLAGS += -Wall
CPPFLAGS += -DVERSION=\"$(VERSION)\"

all: backlight

config.h:
	cp config.def.h config.h

backlight: $(OBJ)

$(OBJ): config.h

dist:
	mkdir -p backlight-$(VERSION)
	cp $(SRC) config.def.h backlight.1 Makefile LICENSE backlight-$(VERSION)
	tar cf - backlight-$(VERSION) | gzip > backlight-$(VERSION).tar.gz
	rm -rf backlight-$(VERSION)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f backlight $(DESTDIR)$(PREFIX)/bin
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	sed "s/VERSION/$(VERSION)/g" < backlight.1 > $(DESTDIR)$(MANPREFIX)/man1/backlight.1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/backlight.1

clean:
	rm -f backlight $(OBJ)

.PHONY: all clean install
