#PROJECT NAME
NAME = philo

#PROJECT FILES
FILES = ft_atol.c philo.c analyze_input.c
INCLUDE = philo.h

#COMPILER
CC = cc
RM = rm -rf

#FLAGS
CFLAGS = -Wall -Wextra -Werror

#OBJECTS
OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "./$(NAME) was created!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 
	@echo "· compiling file.."

clean:
	@$(RM) $(OBJS)
	@echo "object files were deleted!"

fclean: clean
	@$(RM) $(NAME)
	@echo "./$(NAME) was deleted!"

re: fclean all

.PHONY: all fclean clean re