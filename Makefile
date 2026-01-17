CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

tinysh: $(OBJ)
	$(CC) $(CFLAGS) -o tinysh $(OBJ)

clean:
	rm -f src/*.o tinysh
