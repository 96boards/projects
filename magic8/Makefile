CC := g++
LDFLAGS := -lupm-i2clcd -lmraa
CXXFLAGS := -Wall -g
TARGETS := magic8

all: $(TARGETS)

magic8:
	@$(CC) $(CFLAGS) magic8.cpp -o magic8 $(LDFLAGS)

clean:
	rm -f $(TARGETS)
