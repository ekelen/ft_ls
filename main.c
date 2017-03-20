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
	ft_printf("%s\t%s%s", tree->color.fg, tree->path, FG_DEFAULT);
	ft_printf("%s", tree->linkname);
	
	ft_printf("\t%s%s%s", FG_DEFAULT, tree->mtime, FG_DEFAULT);
	if (tree->etype == 'd' && !tree->parentchild)
		ft_printf("\n");
	if (tree->right)
		tree_pr(tree->right);
}


// static int	sub_sort_size(t_ls *new, t_ls **tmpTree, t_ls **tmpNode)
// {

// 	if (!(*tmpTree) || !tmpTree)
// 	{
// 		ft_printf("Some kind of tree error\n");
// 		return (0);
// 	}
// 	//ft_printf("tmpTree-> size : %ld tmpNode->size : %d\n", (*tmpTree)->size, (*tmpNode)->size);
// 	while ((*tmpTree) && ft_strequ(new->dirpath, (*tmpTree)->dirpath))
// 	{
// 		//*tmpNode = *tmpTree;
// 		if (new->size > (*tmpTree)->size)
// 		{
// 			*tmpNode = *tmpTree;
// 			if (ft_strequ(new->dirpath, "/nfs/2016/e/ekelen/1-dir/"))
// 				printf(">>>> [%s] : %lld\t[%s] : %lld\t\n", new->name, new->size, (*tmpTree)->name, (*tmpTree)->size);
// 			*tmpTree = (*tmpTree)->right;
// 			if (!(*tmpTree))
// 			{
// 				(*tmpNode)->right = new;
// 				return(1);
// 			}
// 		}
// 		else
// 		{
// 			if (ft_strequ(new->dirpath, "/nfs/2016/e/ekelen/1-dir/"))
// 				printf("<< [%s] : %lld\t[%s] : %lld\t\n", new->name, new->size, (*tmpTree)->name, (*tmpTree)->size);
// 			*tmpTree = (*tmpTree)->left;
// 			if (!(*tmpTree))
// 			{
// 				(*tmpNode)->left = new;
// 				return(1);
// 			}
// 		}
// 	}
// 	return (1);
// }

// static int	sub_sort_dir(t_ls **tree)
// {
// 	t_ls *tmpTree = *tree;
// 	t_ls *tmpNode;

// 	int diff;

// 	if (!tmpTree)
// 	{
// 		ft_printf("Some kind of tree error\n");
// 		return (0);
// 	}
// 	while (tmpTree)
// 	{
// 		tmpNode = tmpTree;		//each time we move to next node in tree, set the ADDRESS of tmpNode equal to address of tmpTree. (now it's current with tmpTree).
// 		if (new->size > tmpTree)
// 		{
// 			tmpTree = tmpTree->right;
// 			if (!tmpTree)
// 				tmpNode->right = new;	
// 		}
// 		else
// 		{
// 			tmpTree = tmpTree->left;
// 			if (!tmpTree)
// 				tmpNode->left = new;



// 			// else if (new->size > tmpTree->size)
// 			// {
// 			// 	tmpNode = tmpTree;
// 			// 	tmpTree = tmpTree->right;	//tmpNode is now one node behind tmpTree.
// 			// 	if (!tmpTree)
// 			// 		tmpNode->right = new;	//tmpNode->right (at same address of tmpTree) now holds data
// 			// }
// 			// else
// 			// {
// 			// 	tmpNode = tmpTree;
// 			// 	tmpTree = tmpTree->left;	//tmpNode is now one node behind tmpTree.
// 			// 	if (!tmpTree)
// 			// 		tmpNode->left = new;	//tmpNode->right (at same address of tmpTree) now holds data
// 			//}
// 		}
// 	}
// 	return (1);
// }




// static int	sub_sort_dir(t_ls *new, t_ls **tree)
// {
// 	t_ls *tmpTree = *tree;
// 	t_ls *tmpNode;

// 	int diff;

// 	if (!tmpTree)
// 	{
// 		ft_printf("Some kind of tree error\n");
// 		return (0);
// 	}
// 	while (tmpTree)
// 	{
// 		tmpNode = tmpTree;		//each time we move to next node in tree, set the ADDRESS of tmpNode equal to address of tmpTree. (now it's current with tmpTree).
// 		if ((diff = ft_ustrcmp(new->dirpath, tmpTree->dirpath)) > 0)
// 		{
// 			tmpTree = tmpTree->right;
// 			if (!tmpTree)
// 				tmpNode->right = new;
// 			else if (ft_strequ(new->dirpath, tmpTree->dirpath))
// 			{
// 				if (new->size > tmpTree->size)
// 				{
// 					tmpNode = tmpTree;
// 					tmpTree = tmpTree->right;	//tmpNode is now one node behind tmpTree.
// 					if (!tmpTree)
// 						tmpNode->right = new;	//tmpNode->right (at same address of tmpTree) now holds data
// 				}
// 				else
// 				{
// 					tmpNode = tmpTree;
// 					tmpTree = tmpTree->left;	//tmpNode is now one node behind tmpTree.
// 					if (!tmpTree)
// 						tmpNode->left = new;	//tmpNode->right (at same address of tmpTree) now holds data
// 				}
// 			}
// 		}
// 		else
// 		{
// 			tmpTree = tmpTree->left;
// 			if (!tmpTree)
// 				tmpNode->left = new;
// 			else if (ft_strequ(new->dirpath, tmpTree->dirpath))
// 			{
// 				if (new->size > tmpTree->size)
// 				{
// 					tmpNode = tmpTree;
// 					tmpTree = tmpTree->right;	//tmpNode is now one node behind tmpTree.
// 					if (!tmpTree)
// 						tmpNode->right = new;	//tmpNode->right (at same address of tmpTree) now holds data
// 				}
// 				else
// 				{
// 					tmpNode = tmpTree;
// 					tmpTree = tmpTree->left;	//tmpNode is now one node behind tmpTree.
// 					if (!tmpTree)
// 						tmpNode->left = new;	//tmpNode->right (at same address of tmpTree) now holds data
// 				}
// 			}
// 		}
// 	}
// 	//sub_sort_size(tree);
// 	return (1);
// }





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
	else if (sort_mode == 3)
		sort_size(new, tree);
	// else if (sort_mode == 4)
	// 	sub_sort_dir(new, tree);
	
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
	int sort_mode = 3;

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


int		rec_check(char *s, t_opt *e, t_dir cwd)
{
	DIR 				*dir = NULL;
    struct dirent		*dp;
    struct stat			stp;
    struct stat			ltp;
    int					stat_ret = 0;
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
    	if ((stat_ret = stat(path, &stp)) < 0 || (stat_ret = lstat(path, &ltp)) < 0)
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
    tree_pr(cwd.tree);
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
		else if (ft_strchr(s, 'G'))
			flags->ug = 1;
		else if (ft_strchr(s, 'g'))
			flags->g = 1;
		else if (ft_strchr(s, 'p'))
			flags->p = 1;
		else if (ft_strchr(s, 'S'))
			flags->us = 1;
		else
		{
			ft_printf("Found unknown flag\n");
			return (0);
		}
		ft_printf("-%c ", *s);
		s++;
	}
	ft_printf("<< FLAGS\n");

	return (1);
}

int		eval_args(char **s, int ac)
{
	
	t_opt	e;
	t_dir	root;

	root.tree = NULL;

	e.a = 0;
	e.g = 0;
	
	e.l = 0;
	e.p = 0;
	e.r = 0;
	e.ug = 0;
	e.ur = 0;
	e.t = 0;
	int		i;

	i = 0;
	while (i < ac - 1 && s[i][0] == '-')
	{
		if (!(init_opts(s[i], &e)))
			return (0);
		i++;
	}
	rec_check(s[i], &e, root);
	
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
