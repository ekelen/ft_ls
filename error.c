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

void	error(char *s)
{
	ft_printf("ft_ls: ");
	perror(s);
}

// int print_errors(t_opt *e, char **s, int num_paths)
// {
// 	int i;
// 	struct stat stp;

// 	i = 0;
// 	while (i < num_paths)
// 	{
// 		if ((stat(s[i], &stp)) && ((lstat(s[i], &stp))))
// 		{
// 			e->errs++;
// 			error(s[i]);
// 		}
// 		i++;
// 	}
// 	return (1);
// }