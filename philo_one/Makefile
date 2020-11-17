NAME = philo_one
SRCS = philo_one.c utils.c print_status.c get_sizes.c \
		init_funcs.c process.c 
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
LIB = -lpthread
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
