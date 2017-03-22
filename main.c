#include "ft_ls.h"
#include <stdio.h> // DELETE


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
		if (new->lastmod > tmpTree->lastmod)
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

static int	new_tree(t_ls *new, t_ls **tree, t_opt *e)
{
	if (!*tree)
	{
		*tree = new;
		return (1);
	}
	if (e->t)
	{
		ft_printf("Sorting by time.\n");
		sort_time(new, tree);
	}
	else if (e->us)
		sort_size(new, tree);
	else
		sort_ascii(new, tree);
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
		ft_strcpy(new->linkname, " -> ");
		ft_strcat(new->linkname, tmp_link);
	}
	if (new->etype == 'd')
		cwd->dir_meta = new;
	new_tree(new, &(cwd->entries), e);
	return (1);
}









int		init_open(char *s, t_opt *e, t_dir cwd, t_dir **root)
{
	DIR 				*dir = NULL;
    struct dirent		*dp;
    struct stat			stp;
    struct stat			ltp;
    char				path[PATH_MAX];
    int					res = 0;
    
	if ((dir = opendir(s)) == NULL || !s)
		return (0);
	ft_bzero(cwd.path, PATH_MAX);
	ft_strcpy(cwd.path, s);
	cwd.entries = NULL;
	cwd.n = 0;
	while ((dp = readdir(dir)) != NULL)
    {
    	ft_bzero(path, PATH_MAX);
    	ft_strcpy(path, s);
    	ft_strcat(path, "/");
    	ft_strcat(path, dp->d_name);
    	//ft_printf("Trying path : %s\n", dp->d_name);

    	if ((res = stat(path, &stp)) || (lstat(path, &ltp)))
		{
			ft_printf("Problem with path %s (%s) : %d\n", path, dp->d_name, errno);
			break ;
		}
		// else
		// {

		// }
		if (e->ur && S_ISDIR(stp.st_mode) && !ft_strequ(dp->d_name, ".") && !ft_strequ(dp->d_name, ".."))
		{
			init_open(path, e, cwd, root);
		}
					if (S_ISLNK(ltp.st_mode))
			{
				lstat(path, &ltp);
				new_entry(ltp, path, dp, e, &cwd);
			}
			else
				new_entry(stp, path, dp, e, &cwd);
    }
    move_cwd(e, &cwd, root);
    //open_rec(s, e, cwd, root);
    closedir(dir);
    return (1);
}



// static int	init_dir(t_dir *dir)
// {
// 	ft_bzero(dir->path, PATH_MAX);
// 	dir->left = NULL;
// 	dir->right = NULL;
// 	return (1);
// }

int		eval_args(char **s, int ac)
{
	t_opt	e;
	t_dir	cwd;

	t_dir	*root = NULL;
	cwd.entries = NULL;

	zero_opt(&e);
	int		i;

	i = 0;
	while (i < ac - 1 && s[i][0] == '-')
	{
		if (!(init_opts(s[i], &e)))
			return (0);
		i++;
	}
	if(!(init_open(s[i], &e, cwd, &root)))
		ft_printf(ERR_FILE, s[i]);
	meta_pr(root, &e);
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
