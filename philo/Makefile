#PROJECT NAME
NAME = philo

#PROJECT FILES
FILES = ft_atol.c philo.c analyze_input.c init_table.c wrappers.c

#COMPILER
CC = cc
RM = rm -rf

#FLAGS
CFLAGS = -Wall -Wextra -Werror

#COLORS
DEF_COLOR = \e[1;39m
RESET = \e[0m
GRAY = \e[1;90m
RED = \e[1;91m
YELLOW = \e[1;93m
GREEN = \e[1;92m
BLUE = \e[1;94m
MAGENTA = \e[1;95m
CYAN = \e[1;96m
WHITE = \e[1;97m
BLINK = \e[5m

#OBJECTS
OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(WHITE)· $(CYAN)./$(NAME) $(MAGENTA)was created!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 
	@echo "$(WHITE)· $(YELLOW)compiling file: $(BLINK)○$(RESET)"

clean:
	@$(RM) $(OBJS)
	@echo "$(WHITE)· $(RED)all object files were deleted!$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(WHITE)· $(CYAN)./$(NAME) $(RED)was deleted!$(RESET)"

re: fclean all

.PHONY: all fclean clean re
