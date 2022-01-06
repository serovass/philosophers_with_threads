NAME = philo

HEADER = philo.h

LIST =	main_philo.c\
		philo_threads_create.c\
		philo_simulation_fanction.c\
		utils_philo_0.c\
		utils_philo_1.c\
		utils_philo_2.c\

OBJ = ${LIST:.c=.o}

FLAGS = -Wall -Wextra -Werror -pthread -include philo.h

all: $(NAME)

bonus: $(NAME)

%.o: %.c	$(HEADER)
			gcc $(FLAGS) -c $< -o $@

$(NAME):	$(HEADER) $(OBJ)
				gcc $(FLAGS) $(OBJ) -o $(NAME)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re bonus
