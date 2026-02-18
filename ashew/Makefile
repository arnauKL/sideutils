TARGET = ashew
CC = cc
CFLAGS = -Wall -Wextra -pedantic -std=c11
LIBS = -lreadline

all: $(TARGET)

$(TARGET): ashew.c
	$(CC) $(CFLAGS) $(LIBS) ashew.c -o $(TARGET)

.PHONY: run clean

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
