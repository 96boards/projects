CC := gcc
CFLAGS := -Wall -g3
LDFLAGS := -lasound -lm

all: bin

.c.o:
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $<

bin: vu_meter_db.o
	@$(CC) $^ -o $@ $(LDFLAGS)

clean:
	@rm -rf ./bin ./*.o

.PHONY: clean
