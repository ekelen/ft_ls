#include "ft_ls.h"

int	dir_init(t_dir *cwd, char *path)
{
	if (!cwd || !path)
		return(0);
	ft_bzero(cwd->path, PATH_MAX);
	ft_strcpy(cwd->path, path);
	cwd->n = 0;
	cwd->entries = NULL;
	cwd->left = NULL;
	cwd->right = NULL;
	return (1);
}

int		main(int ac, char **av)
{
	t_opt	e;
	char 	**args;
	int 	i;

	zero_opt(&e);
	i = 1;
	args = (char **)malloc(sizeof(char *) * ac + 1);
	if (ac < 2)
	{
		args[0] = ft_strdup(".");
		args[1] = 0;
	}
	else
	{
		while (i < ac)
		{
			args[i - 1] = ft_strdup(av[i]);
			i++;
		}
		i = 0;
		while (i < ac - 1 && args[i][0] == '-')
		{	
			if (!(init_opts(args[i], &e)))
				return (0);
			i++;
		}
		if (i == ac - 1)
		{
			args[i] = ft_strdup(".");
		}
	}
	eval_args(&e, args, ac);
	return (0);
}
