#include "ft_ls.h"


static int str_switch(char **s1, char **s2)
{
	char *tmp;

	tmp = ft_strdup(*s1);
	ft_strdel(s1);
	*s1 = ft_strdup(*s2);
	ft_strdel(s2);
	*s2 = ft_strdup(tmp);
	ft_strdel(&tmp);
	return(1);
}

int		rev_args(char **s, int num_files)
{
	int i;
	int j;

	if (!(s) || !num_files)
		error(1, "rev_args");
	i = 0;
	j = num_files - 1;
	while (s[i])
	{
		if (i != j)
			str_switch(&s[j], &s[i]);
		i++;
		j--;
		
	}
	return (1);
}


static int	extract_files(t_opt *e, char **s, int num_files)
{
	t_dir *file_cwd;
	struct stat stp;
	int i;

	i = 0;
	file_cwd = (t_dir *)ft_memalloc(sizeof(t_dir));
	ft_bzero(file_cwd->path, PATH_MAX);
	ft_strcpy(file_cwd->path, "");
	file_cwd->file_dir = 1;
	file_cwd->n = 0;
	file_cwd->tree = NULL;

	while (i < num_files)
	{
		if (!(stat(s[i], &stp)) || !((lstat(s[i], &stp))))
		{
			if (!(S_ISDIR(stp.st_mode)))
			{
				e->files++;
				new_file_entry(e, stp, file_cwd, s[i]);
			}
			else
			{
				
				e->dirs++;
			}
		}
		i++;
	}
	get_padding(file_cwd, file_cwd->tree, e);
	if (e->r)
		tree_prrv(file_cwd->tree, *file_cwd, e);
	else
		tree_pr(file_cwd->tree, *file_cwd, e);
	//tree_del(file_cwd->tree);
	return (1);
}



static int	sort_args(t_opt *e, char **s, int num_paths) // additional sort
{
	struct stat		stp;
	struct stat		stp2;
	int				i;
	int				j;
	//int				res;

	i = 0;
	j = 0;
	//res = 0;
	while (j < num_paths)
	{
		i = 0;
		while (i + 1 < num_paths - j)
		{
			if ((!(stat(s[i], &stp)) && !(stat(s[i + 1], &stp2))) \
				|| (!(lstat(s[i], &stp) && !(lstat(s[i + 1], &stp2)))))
			{
				if (e->t)
				{
					if (stp.SMT < stp2.SMT)
						str_switch(&s[i], &s[i + 1]);
					else if (stp.SMT == stp2.SMT && stp.SMS < stp2.SMS)
						str_switch(&s[i], &s[i + 1]);
				}	
				else if (e->us)
				{
					if (stp.st_size > stp2.st_size)
						str_switch(&s[i], &s[i+1]);
				}
			}
			// else
			// 	ft_printf("problem with : %s\n", s[i]);
			i++;
		}
		j++;
	}
	if (e->r)
	{
		rev_args(s, num_paths);
	}
	extract_files(e, s, num_paths);
	return (1);
}

static int print_errors(t_opt *e, char **s, int num_paths)
{
	int i;
	struct stat stp;
	//struct stat ltp;
	//int res;

	i = 0;
	while (i < num_paths)
	{
		if ((stat(s[i], &stp)) && ((lstat(s[i], &stp))))
		{
			ft_printf("ft_ls: %s: ", s[i]);
			e->errs++;
			error(1, "");
		}
		i++;
	}
	return (1);
}

static int sort_args_ascii(char **s, int num_paths)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < num_paths)
	{
		i = 0;
		while (i + 1 < num_paths - j)
		{
			if (ft_ustrcmp(s[i], s[i + 1]) > 0)
				str_switch(&s[i], &s[i+1]);
			i++;
		}
		j++;
	}
	return (1);
}

int		eval_args(t_opt *e, char **s, int num_paths)
{
	int					i;
	struct stat 		stp;
	int					first;
	int					res;

	i = 0;
	first = 1;
	sort_args_ascii(s, num_paths);
	print_errors(e, s, num_paths);
	sort_args(e, s, num_paths);
	while (s[i]) //directories (not files) are sent off for printing!
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
	return (1);
}

static int	get_num_paths(int ac, char **av, int *num_flags)
{
	int i;
	int num_paths;

	i = 0;
	num_paths = 0;
	i++;
	while (i < ac && av[i][0] == '-' \
		&& ft_strlen(av[i]) > 1)
	{
		(*num_flags)++;
		i++;
	}
	num_paths = i == ac ? 1 : ac - *num_flags - 1;
	return(num_paths);
}


int		main(int ac, char **av)
{
	t_opt	e;
	char 	**args;
	int 	i;
	int		num_paths;
	int		num_flags;

	num_flags = 0;
	zero_opt(&e);
	i = 1;
	num_paths = get_num_paths(ac, av, &num_flags);
	args = (char **)malloc(sizeof(char *) * (num_paths + 1)); //FREED
	i = 1;
	while (i <= num_flags)
	{
		if (!(init_opts(av[i], &e)))
			return (1);
		i++;
	}
	if (i == ac)
	{
		args[0] = ft_strdup("."); // FREED
		i = 1;
	}
	else
	{
		i = 0;
		while (i < num_paths)
		{
			args[i] = ft_strdup(av[i + 1 + num_flags]); // FREED
			i++;
		}
	}
	args[i] = 0; // FREED
	eval_args(&e, args, num_paths);
	free_args(args, i);
	return (0);
}