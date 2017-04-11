#include "ft_ls.h"

int		eval_args(t_opt *e, char **s, int first)
{
	int					i;
	struct stat 		stp;
	int					res;

	i = 0;
	res = 0;
	sort_args_ascii(e, s);
	if (!e->d)
	{
		while (s[i])
		{
			res = stat(s[i], &stp);
			if (!res && (S_ISDIR(stp.st_mode)))
			{
				if(!(init_dir_open(e, s[i], &first)))
					ft_printf(ERR_FILE, s[i]);
				first = 0;
			}
			i++;
		}
	}
	return (1);
}

static int	get_num_paths(t_opt *e, int ac, char **av, int *num_flags)
{
	int i;
	int num_paths;
	num_paths = 0;
	i = 1;
	
	while (i < ac && av[i][0] == '-' && (init_opts(av[i], e)) \
		&& ft_strlen(av[i]) > 1)
	{
		i++;
		(*num_flags)++;
	}
	num_paths = i == ac ? 1 : ac - *num_flags - 1;
	return(num_paths);
}

char	**get_args(t_opt e, char **args, char **av, int num_flags)
{
	int i;

	i = 0;
	while (i < e.paths)
	{
		args[i] = ft_strdup(av[i + 1 + num_flags]);
		i++;
	}
	args[i] = 0;
	return(args);
}

int		main(int ac, char **av)
{
	t_opt	e;
	char 	**args;
	int 	i;
	int		num_flags;
	int		first;

	first = 1;
	num_flags = 0;
	zero_opt(&e);
	i = 1;
	e.paths = get_num_paths(&e, ac, av, &num_flags);
	args = (char **)malloc(sizeof(char *) * (e.paths + 1));
	if (e.paths == 1 && num_flags == ac - 1)
	{
		args[0] = ft_strdup(".");
		args[1] = 0;
	}
	else
		args = get_args(e, args, av, num_flags);
	eval_args(&e, args, first);
	free_args(args, i);
	return (0);
}