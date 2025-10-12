SRC =	core/main.c core/parsing.c core/philo.c core/philo_routine.c \
		utils/errors.c utils/str.c utils/utils.c utils/time.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Werror -Wextra -I./includes

NAME = philo

DEBUG = debug

SANI = sani

all: $(NAME)


$(NAME): $(OBJ)
	cc $(OBJ) -o $(NAME)

$(DEBUG): $(SRC)
	cc $(CFLAGS) -g3 $(SRC) -o $(DEBUG)

$(SANI): $(SRC)
	cc $(CFLAGS) -g3 $(SRC) -o $(SANI) -fsanitize=thread

clean:
	rm -f */*.o
	rm -f */*/*.o
	rm -f $(LIBFT)/libft.a

fclean: clean
	rm -f $(NAME) $(DEBUG)

re: fclean all

.PHONY: all clean fclean re debug
