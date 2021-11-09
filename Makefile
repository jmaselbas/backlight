# See LICENSE file for copyright and license details.
# Install paths
PREFIX := /usr/local

CFLAGS += -Wall

all: backlight

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f backlight $(DESTDIR)$(PREFIX)/bin

clean:
	rm -f backlight

.PHONY: all clean install
