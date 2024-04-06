CC = gcc
CFLAGS = -Wall -g
LDFLAGS =

# executable name
EXECUTABLE = practicum

SRCS = $(wildcard *.c)
OBJECTS = $(SRCS:.c=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o "$@"

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)