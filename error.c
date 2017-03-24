# include "ft_ls.h"

void	error(int err)
{
	ft_putstr_fd(strerror(err), 2);
	exit(EXIT_FAILURE);
}