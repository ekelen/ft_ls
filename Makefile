NAME	= ft_ls

SRC		+=	main.c
# SRC		+=  ft_catpath.c
SRC		+= ft_ustrcmp.c
SRC		+= tmp_get_data.c

SRC		+= padding.c
SRC		+= parse_args.c
SRC		+= print.c
SRC		+= time.c

SRC		+= ft_numlen.c
SRC		+= ft_abs.c

OBJ		= $(SRC:.c=.o)

CFLAGS	= -g -Wall -Wextra -Werror

$(NAME): $(OBJ)
	make -C libft/
	make -C printf/
	gcc $(OBJ) -o $(NAME) -L libft -lft -L printf -lftprintf

all: $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME) $(OBJ)

re: fclean $(NAME)
