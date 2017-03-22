#include "ft_ls.h"

size_t	ft_numlen(unsigned int nbr)
{
	size_t num_len;

	num_len = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		num_len++;
	}
	return (num_len);
}