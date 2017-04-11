#include "ft_ls.h"

int		rev_args(t_opt *e, char **s)
{
	int i;
	int j;

	if (!(s) || !e->paths)
		error("rev_args");
	i = 0;
	j = e->paths - 1;
	while (s[i])
	{
		if (i != j)
			str_switch(&s[j], &s[i]);
		i++;
		j--;
		
	}
	return (1);
}


static void	make_file_dir(t_opt *e, char **s, t_dir *file_cwd)
{
	struct stat stp;
	int i;

	i = 0;
	zero_dir(file_cwd, "");
	file_cwd->file_dir = 1;
	while (i < e->paths)
	{
		if (!(stat(s[i], &stp)) || !((lstat(s[i], &stp))))
		{
			if (!(S_ISDIR(stp.st_mode)) || e->d)
			{
				e->files++;
				new_file_entry(e, stp, file_cwd, s[i]);
			}
			else
				e->dirs++;
		}
		i++;
	}
	get_padding(file_cwd, file_cwd->tree, e);
	return ;
}

static int	extract_files(t_opt *e, char **s)
{
	t_dir *file_cwd;
	
	file_cwd = (t_dir *)ft_memalloc(sizeof(t_dir));
	make_file_dir(e, s, file_cwd);
	if (e->r)
		tree_prrv(file_cwd->tree, *file_cwd, e);
	else
		tree_pr(file_cwd->tree, *file_cwd, e);
	tree_del(file_cwd->tree);
	free(file_cwd);
	return (1);
}

static void	sort_args_stp(t_opt *e, char **s, int i)
{
	struct stat		stp;
	struct stat		stp2;

	if ((!(stat(s[i], &stp)) && !(stat(s[i + 1], &stp2))) \
				|| (!(lstat(s[i], &stp) && !(lstat(s[i + 1], &stp2)))))
	{			
		if (e->us)
		{
			if (stp.st_size < stp2.st_size)
				str_switch(&s[i], &s[i+1]);
		}
		else if (e->t)
		{
			if (stp.SMT < stp2.SMT)
				str_switch(&s[i], &s[i + 1]);
			else if (stp.SMT == stp2.SMT && stp.SMS < stp2.SMS)
				str_switch(&s[i], &s[i + 1]);
		}
	}
	return ;
}


static int	sort_args(t_opt *e, char **s)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (j < e->paths)
	{
		i = 0;
		while (i + 1 < e->paths - j)
		{
			sort_args_stp(e, s, i);
			i++;
		}
		j++;
	}
	if (e->r)
		rev_args(e, s);
	extract_files(e, s);
	return (1);
}

static int sort_args_ascii(t_opt *e, char **s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < e->paths)
	{
		i = 0;
		while (i + 1 < e->paths - j)
		{
			if (ft_ustrcmp(s[i], s[i + 1]) > 0)
				str_switch(&s[i], &s[i+1]);
			i++;
		}
		j++;
	}
	print_errors(e, s);
	sort_args(e, s);
	return (1);
}

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