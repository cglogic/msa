TARGET=msa
VERSION=0.1

PREFIX?=/usr/local

CPPFLAGS=-DVERSION=\"${VERSION}\"
CFLAGS+=-Wall -Wextra -std=c11 -pedantic -I$(PREFIX)/include $(CPPFLAGS)
LDFLAGS=-L$(PREFIX)/lib

MANDIR?=$(PREFIX)/man/man1
BINDIR?=$(PREFIX)/bin

INSTALL=install
INSTALL_PROGRAM=$(INSTALL)
INSTALL_DATA=${INSTALL} -m 644

LIBS=-lpthread -lncurses
OBJECTS=src/main.o src/network.o src/stream.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -fv $(OBJECTS)
	rm -fv $(TARGET)

install: msa
	mkdir -p $(DESTDIR)$(BINDIR)
	cp $(TARGET) $(DESTDIR)$(BINDIR)/
	chmod 755 ${DESTDIR}${BINDIR}/$(TARGET)

run:
	./$(TARGET)
