CC := g++
LDFLAGS := -lupm-i2clcd -lupm-mma7660
CXXFLAGS := -Wall -Wextra -g

all:accel

accel:
	@$(CC) $(CFLAGS) accel.cpp -o bin $(LDFLAGS)
clean:
	rm -f ./bin
