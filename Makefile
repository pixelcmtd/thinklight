CC ?= cc
PREFIX ?= /usr/local

all: thinklight capslock standby power wifi

%: %.c
	$(CC) -Wall -Wextra -O3 $< -o $@
	chmod +s $@

install:
	cp thinklight capslock standby power wifi /usr/local/bin/
	chmod +s $(PREFIX)/bin/thinklight $(PREFIX)/bin/capslock \
		$(PREFIX)/bin/standby $(PREFIX)/bin/power $(PREFIX)/bin/wifi

.PHONY: all install
