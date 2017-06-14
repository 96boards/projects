CC := g++
LDFLAGS=-lupm-i2clcd
CXXFLAGS=-Wall -g
TARGETS=$(TARGETS)

all: hourglass

hourglass:
	@$(CC) $(CFLAGS) hourglass.cpp -o hourglass $(LDFLAGS)

clean:
	rm -f ./hourglass
