TARGET = ashew
CC = cc
CFLAGS = -Wall -Wextra -pedantic -std=c11

all: $(TARGET)

$(TARGET): ashew.c
	$(CC) $(CFLAGS) ashew.c -o $(TARGET)

.PHONY: run clean

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
