EXECUTABLE = a

CC = gcc

CFLAGS = -Wall

SRC = a.c

OBJ = $(SRC:.c=.o)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE)

%.o:  %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJ)
