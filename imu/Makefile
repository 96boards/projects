CC := gcc
LDFLAGS := -lmraa -lm
CFLAGS := -Wall -Wextra -g3
SRCDIR := src
OBJDIR := obj

all: dirs imu

imu: $(OBJDIR)/imu.o
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $^

dirs:
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR) imu

.PHONY: all dirs clean
