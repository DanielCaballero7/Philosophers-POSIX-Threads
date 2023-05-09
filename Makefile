NAME = philo
SRCS = src/main.c src/utils.c src/ft_atoi.c src/ft_isdigit.c src/master_checks.c
CC = gcc -g
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all fclean clean re