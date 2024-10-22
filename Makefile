SOURCES = *.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = a.out

$(NAME): $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS)

debug:
	$(CC) -fsanitize=address -g $(SOURCES) $(CFLAGS)

clean:
	rm -f $(NAME)

re: clean
	$(CC) $(SOURCES) $(CFLAGS)