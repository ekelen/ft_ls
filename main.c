#include "ft_ls.h"

static int str_switch(char *s1, char *s2)
{
	char *tmp;

	tmp = ft_strdup(s1);
	ft_strdel(&s1);
	s1 = ft_strdup(s2);
	ft_strdel(&s2);
	s2 = ft_strdup(tmp);
	ft_strdel(&tmp);
	return(1);
}

static int sort_args_time(char **s, int num_files)
{
	struct stat		stp;
	struct stat		stp2;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (j < num_files)
	{
		i = 0;
		while (i + 1 < num_files - j)
		{
			if ((stat(s[i], &stp)) != 0)
			error(1, "sort arg time error");
			if ((stat(s[i + 1], &stp2)) != 0)
			error(1, "sort arg time error");
			if (stp.st_mtime < stp2.st_mtime)
				str_switch(s[i], s[i+1]);
			else if (stp.SMT == stp2.SMT && stp.SMS < stp2.SMS)
				str_switch(s[i], s[i+1]);	
			i++;
		}
		j++;

	}
	return(1);
}

static int sort_args_ascii(char **s, int num_files)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < num_files)
	{
		i = 0;
		while (i + 1 < num_files - j)
		{
			if (ft_ustrcmp(s[i], s[i + 1]) > 0)
				str_switch(s[i], s[i+1]);
			i++;
		}
		j++;
	}
	return (1);
}

int	sort_args(t_opt *e, char **s, int num_files)
{
	int i;
	struct stat stp;
	int err;
	int num_dirs;

	i = 0;
	num_dirs = num_files;
	while (s[i])
	{
		if ((err = stat(s[i], &stp)) != 0)
			error(err, "sort arg ascii error");
		if (!(S_ISDIR(stp.st_mode)))
		{
			e->files = 1;
			num_dirs--;
		}
		i++;
	}
	e->dirs = num_dirs > 1 ? 1 : 0;
	sort_args_ascii(s, num_files);
	if (e->t)
		sort_args_time(s, num_files);
	// else if (e->us)
	// 	sort_args_size(s, num_files);
	return (1);
}

static int	handle_files(t_opt *e, char **s)
{
	t_dir *file_cwd;
	struct stat stp;
	int i;
	int err;

	i = 0;
	file_cwd = (t_dir *)ft_memalloc(sizeof(t_dir));
	ft_bzero(file_cwd->path, PATH_MAX);
	ft_strcpy(file_cwd->path, "");
	//file_cwd->first = 1;
	file_cwd->parent = 1;
	file_cwd->n = 0;
	file_cwd->tree = NULL;
	while (s[i])
	{
		if ((err = stat(s[i], &stp)) != 0)
			error(err, "handle files error");
		if (!(S_ISDIR(stp.st_mode)))
		{
			new_file_entry(e, stp, file_cwd, s[i]);
		}
		i++;
	}
	if (e->r)
		tree_prrv(file_cwd->tree, *file_cwd, e);
	else
	{
		tree_pr(file_cwd->tree, *file_cwd, e);
	}
	return (1);
}


int		eval_args(t_opt *e, char **s, int num_files)
{
	int					i;
	int					err;
	struct stat 		stp;
	int					first;
	int					parent;

	i = 0;
	parent = 1;
	first = 1;
	sort_args(e, s, num_files);
	if (e->files)
	{
		handle_files(e, s);
	}
	while (s[i])
	{
		if ((err = stat(s[i], &stp)) != 0)
			error(err, "EVAL STAT ERROR");
		if ((S_ISDIR(stp.st_mode)))
		{
			if(!(init_dir_open(e, s[i], &first, &parent)))
				ft_printf(ERR_FILE, s[i]);
			first = 0;
		}
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
	i++;
	while (i < ac && av[i][0] == '-')
	{
		(*num_flags)++;
		i++;
	}
	num_files = i == ac ? 1 : ac - *num_flags - 1;
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
			i++;
		}
	}
	args[i] = 0;
	eval_args(&e, args, num_files);
	return (0);
}
