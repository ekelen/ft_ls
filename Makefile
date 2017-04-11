# ----------------------------------------------------------------------------
# COLORES |
# ----------------------------------------------------------------------------
 RESET=\033[0m
 DARK=\033[132m
 RED=\033[31m
 GREEN=\033[32m
 YELLOW=\033[33m
 BLUE=\033[34m
 MAGENTA=\033[35m
 CYAN=\033[36m
 WHITE=\033[37m
 BOLDBLACK=\033[1m\033[30m
 BOLDRED=\033[1m\033[31m
 BOLDWHITE=\033[1m\033[37m

# ----------------------------------------------------------------------------
# VARIABLES |
# ----------------------------------------------------------------------------

.PHONY: all, clean, fclean, re

NAME	= ft_ls

SRC		+= color.c
SRC		+= delete.c
SRC		+= entry.c
SRC		+= error.c
SRC		+= file.c
SRC		+= main.c
SRC		+= open.c
SRC		+= open_2.c
SRC		+= padding.c
SRC		+= parse_args.c
SRC		+= print.c
SRC		+= print_2.c
SRC		+= sort.c 
SRC		+= sort_args.c
SRC		+= stat.c
SRC		+= time.c
SRC		+= tools.c

OBJ_PATH = ./obj/
OBJ_NAME = $(SRC:.c=.o)
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

CFLAGS	= -Wall -Wextra -Werror

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)
	@gcc $(CFLAGS) -o $@ -c $<
	@echo -n .

$(NAME): $(OBJ)
	@echo "\n[${GREEN}$(NAME) done${RESET}.]"
	@make -C libft/
	@make -C printf/
	@gcc $(OBJ) -o $(NAME) -L libft -lft -L printf -lftprintf

all: $(NAME)

clean:
	@rm -rf $(OBJ_PATH)
	@make -C libft/ clean
	@make -C printf/ clean

fclean: clean
	@rm -rf $(NAME)

re: fclean $(NAME)
	@make -C libft/ re
	@make -C printf/ re
