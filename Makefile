# Install paths
PREFIX := /usr/local

all: backlight

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f backlight $(DESTDIR)$(PREFIX)/bin