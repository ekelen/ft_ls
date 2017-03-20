#include "ft_ls.h"
#include <stdio.h> // DELETE

static void	tree_pr(t_ls *tree)
{
	if (!tree)
		return ;
	//ft_printf("%c %c%c%c %s %s  %s %ld\t", tree->etype, tree->acc.ruser, tree->acc.wuser, tree->acc.xgrp, tree->uid_name, tree->path, tree->grp_name, tree->hlinks);
	//ft_printf("%d\n", tree->which);
	//ft_printf("%s\n", tree->path);
	//ft_printf("%ld bytes\n", tree->size);
	
	if (tree->left)
		tree_pr(tree->left);
	//ft_printf("%d : %s\n", tree->hmtime, tree->path);
	ft_printf("%c%c%c%c %ld %s %s %s %s   ", tree->etype, tree->acc.ruser, tree->acc.wuser, tree->acc.xgrp, tree->hlinks, tree->uid_name, tree->path, tree->linkname, tree->grp_name);
	ft_printf("%ld bytes  ", tree->size);
	ft_printf("%s", tree->mtime);
	if (tree->right)
		tree_pr(tree->right);
}

// static void	tree_revpr(t_ls *tree)
// {
// 	if (!tree)
// 		return ;
// 	//ft_printf("%c %c%c%c %s %s  %s %ld\t", tree->etype, tree->acc.ruser, tree->acc.wuser, tree->acc.xgrp, tree->uid_name, tree->path, tree->grp_name, tree->hlinks);
// 	//ft_printf("%d\n", tree->which);
// 	//ft_printf("%s\n", tree->path);
// 	//ft_printf("%ld bytes\n", tree->size);
	
// 	if (tree->right)
// 		tree_pr(tree->right);
// 	ft_printf("%d : %s\n", tree->hmtime, tree->path);
// 	if (tree->left)
// 		tree_pr(tree->left);
// }

static int	sort_time(t_ls *new, t_ls **tree)
{
	t_ls *tmpTree = *tree;
	t_ls *tmpNode;

	if (!tmpTree)
	{
		ft_printf("Some kind of tree error\n");
		return (0);
	}
	while (tmpTree)
	{
		tmpNode = tmpTree;
		if (new->hmtime > tmpTree->hmtime)
		{
			tmpTree = tmpTree->right;
			if (!tmpTree)
			{
				tmpNode->right = new;
			}
		}
		else
		{
			tmpTree = tmpTree->left;
			if (!tmpTree)
				tmpNode->left = new;
		}
	}
	return (1);
}


static int	sort_ascii(t_ls *new, t_ls **tree)
{
	t_ls *tmpTree = *tree;
	t_ls *tmpNode;

	int diff;

	if (!tmpTree)
	{
		ft_printf("Some kind of tree error\n");
		return (0);
	}
	while (tmpTree)
	{
		tmpNode = tmpTree;		//each time we move to next node in tree, set the ADDRESS of tmpNode equal to address of tmpTree. (now it's current with tmpTree).
		if ((diff = ft_ustrcmp(new->path, tmpTree->path)) > 0)
		{
			tmpTree = tmpTree->right;	//tmpNode is now one node behind tmpTree.
			if (!tmpTree)
				tmpNode->right = new;	//tmpNode->right (at same address of tmpTree) now holds data
		}
		else
		{
			tmpTree = tmpTree->left;
			if (!tmpTree)
				tmpNode->left = new;
		}
	}
	return (1);
}

static int	new_tree(t_ls *new, t_ls **tree, int sort_mode)
{
	if (!*tree)
	{
		*tree = new;
		return (1);
	}
	if (sort_mode == 1)
		sort_ascii(new, tree);
	else if (sort_mode == 2)
		sort_time(new, tree);
	return (1);
}


int		new_entry(struct stat stp, char *path, struct dirent *dp, t_ls **tree)
{
	int sort_mode = 1;
	static int which = 1;
	if (!(path || dp || tree))
		return (0);
	t_ls *new;
	char	tmp_link[PATH_MAX];
	new = malloc(sizeof(t_ls));
	ft_bzero(new->uid_name, NAME_MAX);
	ft_bzero(new->grp_name, NAME_MAX);
	ft_bzero(new->linkname, PATH_MAX);
	ft_bzero(tmp_link, PATH_MAX);
	if (!(get_type(stp, path, dp, new)))
	{
		ft_printf("stat_init failed.\n");
		return (0);
	}
	ft_bzero(new->name, NAME_MAX);
	ft_bzero(new->path, PATH_MAX);
	
	ft_strcpy(new->name, dp->d_name);
	ft_strcpy(new->path, path);
	new->d_ino = dp->d_ino;
	new->right = NULL;
	new->left = NULL;
	new->which = which;
	which++;

	if (S_ISLNK(stp.st_mode))
	{
		readlink(new->path, tmp_link, PATH_MAX);
		ft_strcpy(new->linkname, " ->    ");
		ft_strcat(new->linkname, tmp_link);
		//ft_printf("link path : %s\n", new->linkname);
	}
	new_tree(new, tree, sort_mode);
	return (1);
}


int		rec_check(char *s, t_ls **tree)
{
	DIR 				*dir = NULL;
    struct dirent		*dp;
    struct stat			stp;
    struct stat			ltp;
    int					stat_ret = 0;
    char				path[PATH_MAX];
    //char				linkname[PATH_MAX];

	if ((dir = opendir(s)) == NULL || !s)
		return (0);
	while ((dp = readdir(dir)) != NULL)
    {
    	ft_bzero(path, PATH_MAX);
    	ft_strcpy(path, s);
    	ft_strcat(path, "/");
    	ft_strcat(path, dp->d_name);

    	if ((stat_ret = stat(path, &stp)) < 0 || (stat_ret = lstat(path, &ltp)) < 0)
		{
			ft_printf("Problem with path %s (%s) : %d\n", path, dp->d_name, errno);
			break ;
			;
		}
		else
		{
			if (S_ISLNK(ltp.st_mode))
			{
				lstat(path, &ltp);
				new_entry(ltp, path, dp, tree);
			}
			else
				new_entry(stp, path, dp, tree);
		}
		if (S_ISDIR(stp.st_mode) && !ft_strequ(dp->d_name, ".") && !ft_strequ(dp->d_name, ".."))
		{
			rec_check(path, tree);
		}
    }
    closedir(dir);
    return (0);
}

int		init_opts(char *s, t_opt *flags)
{
	s++;
	while (*s)
	{
		if (ft_strchr(s, 'a'))
			flags->a = 1;
		else if (ft_strchr(s, 't'))
			flags->t = 1;
		else if (ft_strchr(s, 'R'))
			flags->ur = 1;
		else if (ft_strchr(s, 'r'))
			flags->r = 1;
		else if (ft_strchr(s, 'l'))
			flags->l = 1;
		else
		{
			ft_printf("Found unknown flag\n");
			return (0);
		}
		s++;
	}

	return (1);
}

int		eval_args(char **s, int ac)
{
	t_ls	*tree;
	t_opt	flags;
	flags.ur = 0;
	flags.r = 0;
	flags.t = 0;
	flags.a = 0;
	int		i;

	i = 0;
	tree = NULL;
	
	while (i < ac - 1 && s[i][0] == '-')
	{
		if (!(init_opts(s[i], &flags)))
			return (0);
		i++;
	}
	rec_check(s[i], &tree);
	tree_pr(tree);
	return (0);
}


int		main(int ac, char **av)
{
	char **args;
	int i;

	i = 1;
	args = (char **)malloc(sizeof(char *) * ac);
	if (ac < 2)
	{
		printf("handle multiple inputs soon....\n");
		return (0);
	}
	while (i < ac)
	{
		args[i - 1] = ft_strdup(av[i]); //FREE
		printf("args[i - 1] : %s\n", args[i - 1]);
		i++;
	}
	eval_args(args, ac);
	
	



	//ft_printf("Test\n");

	//-l, -R, -a, -r and -t
	//l = "long"
	//-a = include things with a dot
	//-t == sort by time
	//-r == reverse order
	//-R == recursively list subdirectories encountered

	//BONUS TODO:
	//-h (uses unit instead of size)
	//-m (stream output across the page, separated by commas)
	//-p (add a slash after each directory found
	//-S sort files by size
	//-o same as -l but without group id
	//-G colorized output
	//invent your own (ask if want to list ? search directory ?)
	//-A list all entries except . and ..

	
	return (0);
}
