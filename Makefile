NAME	= ft_ls

SRC		+=	main.c
SRC		+=  ft_catpath.c

OBJ		= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

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
