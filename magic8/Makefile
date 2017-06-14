CC := g++
LDFLAGS= -lupm-i2clcd -lmraa
CXXFLAGS=-Wall -g
TARGETS=$(TARGETS)

all: magic8

magic8:
	@$(CC) $(CFLAGS) magic8.cpp -o magic8 $(LDFLAGS)

clean:
	rm -f magic8
