NAME = philo

CFLAGS = -Wall -Wextra -Werror

SRCS =	main.c \
		utils.c \
		life_cycle.c \
		monitor.c \
		threads.c \
		initialize.c \

OBJ = $(SRCS:.c=.o)

all: $(NAME)  

$(NAME): $(OBJ)
	cc $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all