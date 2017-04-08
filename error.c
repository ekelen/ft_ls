# include "ft_ls.h"

void	usage_err(char c)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: ./ft_ls ", 2);
	ft_putstr_fd(VALID_OPT, 2);
	ft_putstr_fd(" [file ...]\n", 2);
	exit(1);
}

void	error(int err, char *s)
{
	ft_printf("ft_ls: ");
	perror(s);
	if (err == 2)
		exit(1);
}