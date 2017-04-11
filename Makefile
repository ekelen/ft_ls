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

SRC		+= main.c
SRC		+= color.c
SRC		+= entry.c
SRC		+= error.c
SRC		+= ft_catpath.c
SRC		+= padding.c
SRC		+= parse_args.c
SRC		+= parse_args_2.c
SRC		+= sort_args.c
SRC		+= tmp_get_data.c
SRC		+= print.c
SRC		+= print_2.c
SRC		+= sort.c 
SRC		+= time.c
SRC		+= open.c
SRC		+= delete.c

OBJ_PATH = ./obj/
OBJ_NAME = $(SRC:.c=.o)
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

CFLAGS	= -g -Wall -Wextra -Werror

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)
	@gcc $(CFLAGS) -o $@ -c $<
	@echo -n .

$(NAME): $(OBJ)
	@echo "[${GREEN}$(NAME) done${RESET}]"
	@make -C libft/
	@make -C printf/
	@gcc $(OBJ) -o $(NAME) -L libft -lft -L printf -lftprintf

all: $(NAME)

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(NAME)

re: fclean $(NAME)
