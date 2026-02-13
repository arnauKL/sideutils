CC = cc
CFLAGS = -Wall -Wextra -pedantic -std=c11

# `cat.c` becomes `cat` 
BINS = $(SRCS:.c=)
SRCS = $(wildcard *.c)


.PHONY: all clean

all: $(BINS)

# 'cat' looks for 'cat.c'
%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BINS)
