NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c src/string_utils.c src/time_utils.c src/philo.c src/log.c src/thread_and_mutex.c src/monitor.c src/fork.c src/free.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

run:$(NAME)
	valgrind --track-origins=yes --leak-check=full -s ./philo 1 410 200 200

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re