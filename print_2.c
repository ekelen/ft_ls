#include "ft_ls.h"

void	pr_dec(size_t print, size_t width, size_t align)
{
	size_t i;

	i = 0;
	if (align)
		ft_printf("%zd", print);
	if (ft_numlen(print) < width)
	{
		while (ft_numlen(print) + i < width)
		{
			ft_putchar(' ');
			i++;
		}
	}
	if (!align)
		ft_printf("%zd", print);
	return ;
}

void	pr_str(char *print, size_t width, int align)
{
	size_t i;

	i = 0;
	if (align)
		ft_printf("%s", print);
	if (ft_strlen(print) < width)
	{
		while (ft_strlen(print) + i < width)
		{
			ft_putchar(' ');
			i++;
		}
	}
	if (!align)
		ft_printf("%s", print);
	ft_putchar(' ');
	return ;
}