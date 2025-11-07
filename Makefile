SRC =	core/main.c core/parsing.c core/philo.c core/philo_routine.c \
		core/charon_routine.c \
		utils/errors.c utils/str.c utils/utils.c utils/time.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Werror -Wextra -I./includes

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) -o $(NAME)

clean:
	rm -f */*.o
	rm -f */*/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
