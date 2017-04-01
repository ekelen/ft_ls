#include "ft_ls.h"


int		eval_args(t_opt *e, char **s)
{
	int					i;
	int					err;
	t_dir				*cwd;
	struct stat stp;


	i = 0;
	while (s[i])
	{
		cwd = malloc(sizeof(t_dir));
		if ((err = stat(s[i], &stp)) != 0)
			error(err, "EVAL STAT ERROR");
		if (!(S_ISDIR(stp.st_mode)))
		{
			// files = 1;
			;
			//dir_init(cwd, "VOID", 1);
			//new_entry(stp, s[i], e, cwd);
		}
		else
		{
			//ft_printf("s : %s\n", s[i]);
			if (!(dir_init(cwd, s[i], 0)))
			{
				//ft_printf("dir init failed.\n");
				ft_printf(ERR_FILE, s[i]);
			}
			if(!(init_open(s[i], e, *cwd)))
				ft_printf(ERR_FILE, s[i]);
		}
		free(cwd);
		i++;
	}
	return (1);
}

static int	get_num_files(int ac, char **av, int *num_flags)
{
	int i;
	int num_files;

	i = 0;
	num_files = 0;
	i++; // skip program name
	while (i < ac && av[i][0] == '-')
	{
		(*num_flags)++;
		i++;
	}
	num_files = i == ac ? 1 : ac - *num_flags - 1;
		// ft_printf("num_files : %d\n", num_files);
	return(num_files);
}

int		main(int ac, char **av)
{
	t_opt	e;
	char 	**args;
	int 	i;
	int		num_files;
	int		num_flags;

	num_flags = 0;
	zero_opt(&e);
	i = 1;
	num_files = get_num_files(ac, av, &num_flags);
	args = (char **)malloc(sizeof(char *) * (num_files + 1));
	i = 1;
	while (i <= num_flags)
	{
		if (!(init_opts(av[i], &e)))
			return (1);
		i++;
	}
	if (i == ac)
	{
		args[0] = ft_strdup(".");
		i = 1;
	}
	else
	{
		i = 0;
		while (i < num_files)
		{
			args[i] = ft_strdup(av[i + 1 + num_flags]);
			//ft_printf("args[%d] : %s\n", i, args[i]);
			i++;
		}
	}
	args[i] = 0;
	eval_args(&e, args);
	return (0);
}
