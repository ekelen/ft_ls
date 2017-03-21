#include "ft_ls.h"
#include <stdio.h> // DELETE

static void	tree_pr(t_ls *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		tree_pr(tree->left);
	ft_printf("%c%c%c%c%c%c%c%c%c%c", tree->etype, tree->acc.ruser, tree->acc.wuser, tree->acc.xuser, tree->acc.rgrp, tree->acc.wgrp, tree->acc.xgrp, tree->acc.roth, tree->acc.woth, tree->acc.xoth);
	ft_printf("% ld\t%-s %s", tree->hlinks, tree->uid_name, tree->grp_name);
	
	ft_printf("\t%ld", tree->size);
	ft_printf("%s\t%s%s", tree->color.fg, tree->name, FG_RESET);
	ft_printf("%s", tree->linkname);
	
	ft_printf("\t%s%s%s", FG_RESET, tree->mtime, FG_RESET);
	if (tree->right)
		tree_pr(tree->right);
}


static int	sort_size(t_ls *new, t_ls **tree)
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
		if (new->size > tmpTree->size)
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
				tmpNode->right = new;
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
	//ft_printf("--- > \n%s\n", new->path);
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
	else if (sort_mode == 3)
		sort_size(new, tree);
	return (1);
}


t_ls	zero_entry(char *path, t_ls *new, struct dirent *dp)
{
	static int which = 0;
	ft_bzero(new->name, NAME_MAX);
	ft_bzero(new->path, PATH_MAX);
	ft_strcpy(new->name, dp->d_name);
	ft_strcpy(new->path, path);
	ft_bzero(new->uid_name, NAME_MAX);
	ft_bzero(new->grp_name, NAME_MAX);
	ft_bzero(new->linkname, PATH_MAX);
	new->d_ino = dp->d_ino;
	new->right = NULL;
	new->left = NULL;
	new->which = which;
	which++;
	return (*new);
}

int		new_entry(struct stat stp, char *path, struct dirent *dp, t_opt *e, t_dir *cwd)
{
	int sort_mode = 1;

	if (!(path || dp))
		return (0);
	t_ls	*new;
	char	tmp_link[PATH_MAX];

	new = malloc(sizeof(t_ls));
	*new = zero_entry(path, new, dp);
	
	ft_bzero(tmp_link, PATH_MAX);
	if (!(get_type(stp, e, new)))
	{
		ft_printf("stat_init failed.\n");
		return (0);
	}
	if (new->etype == 'l')
	{
		readlink(new->path, tmp_link, PATH_MAX);
		ft_strcpy(new->linkname, " ->  ");
		ft_strcat(new->linkname, tmp_link);
	}
	new_tree(new, &(cwd->tree), sort_mode);
	return (1);
}

// static void meta_pr(t_dir *tree)
// {
// 	if (!tree)
// 		return ;
// 	//ft_printf("\t%s%s%s", FG_GREEN, tree->path, FG_DEFAULT);
// 	if (tree->left)
// 	{
// 		ft_printf("Moves to the left: %s\n ", tree->path);
// 		meta_pr(tree->left);
// 	}
// 	ft_printf("\t%s%s%s", FG_GREEN, tree->path, FG_DEFAULT);
// 	if (tree->right)
// 		meta_pr(tree->right);
// }



// static int	sort_dirs_ascii(t_dir *new, t_dir **tree)
// {
// 	t_dir *tmpTree = *tree;
// 	t_dir *tmpNode;

// 	int diff;

// 	if (!tmpTree)
// 	{
// 		*tree = new;
// 		return (1);
// 	}
// 	while (tmpTree)
// 	{
// 		tmpNode = tmpTree;		//each time we move to next node in tree, set the ADDRESS of tmpNode equal to address of tmpTree. (now it's current with tmpTree).
// 		if ((diff = ft_ustrcmp(new->path, tmpTree->path)) > 0)
// 		{
// 			tmpTree = tmpTree->right;	//tmpNode is now one node behind tmpTree.
// 			if (!tmpTree)
// 			{
// 				tmpNode->right = new;	//tmpNode->right (at same address of tmpTree) now holds data
// 			}
// 		}
// 		else
// 		{
// 			tmpTree = tmpTree->left;
// 			if (!tmpTree)
// 			{
// 				tmpNode->left = new;
// 			}
// 		}
// 	}
// 	return (1);
// }

// int		move_cwd(t_dir *cwd, t_opt *e)
// {
// 	//e->tree_tree = cwd;
// 	//tree_pr(e->tree_tree->tree);
// 	if (!cwd || !e)
// 		return (0);
// 	sort_dirs_ascii(cwd, &(e->tree_tree));
// 	return (1);
//}

int		move_cwd(t_dir *cwd)
{
	//e->tree_tree = cwd;
	tree_pr(cwd->tree);
	return (0);
}


int		rec_check(char *s, t_opt *e, t_dir cwd)
{
	DIR 				*dir = NULL;
    struct dirent		*dp;
    struct stat			stp;
    struct stat			ltp;
    char				path[PATH_MAX];
    

	if ((dir = opendir(s)) == NULL || !s)
		return (0);
	ft_bzero(cwd.path, PATH_MAX);
	ft_strcpy(cwd.path, s);
	cwd.tree = NULL;

	while ((dp = readdir(dir)) != NULL)
    {
    	ft_bzero(path, PATH_MAX);
    	ft_strcpy(path, s);
    	ft_strcat(path, "/");
    	ft_strcat(path, dp->d_name);
    	if ((stat(path, &stp)) || (lstat(path, &ltp)))
		{
			ft_printf("Problem with path %s (%s) : %d\n", path, dp->d_name, errno);
			break ;
		}
		else
		{
			if (S_ISLNK(ltp.st_mode))
			{
				lstat(path, &ltp);
				new_entry(ltp, path, dp, e, &cwd);
			}
			else
				new_entry(stp, path, dp, e, &cwd);
		}
		if (S_ISDIR(stp.st_mode) && !ft_strequ(dp->d_name, ".") && !ft_strequ(dp->d_name, ".."))
		{
			
			rec_check(path, e, cwd);
		}
    }
    ft_printf("\n%s\n", cwd.path);
    move_cwd(&cwd);
    
    closedir(dir);
    return (0);
}





int		eval_args(char **s, int ac)
{
	
	t_opt	e;
	t_dir	root;
	//e.tree_tree = NULL;
	root.tree = NULL;	

	zero_opt(&e);
	int		i;

	i = 0;
	while (i < ac - 1 && s[i][0] == '-')
	{
		if (!(init_opts(s[i], &e)))
			return (0);
		i++;
	}
	//get_padding(s[i], &e, &root);
	rec_check(s[i], &e, root);
	//ft_printf("~~~~~~~~~~~\n");
	//ft_printf("Signs of life?? %s %s\n", root.path, e.tree_tree->path);
	//meta_pr(e.tree_tree);
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
		i++;
	}
	eval_args(args, ac);
	return (0);
}
