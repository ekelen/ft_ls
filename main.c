#include "ft_ls.h"
#include <stdio.h> // DELETE

static void	tree_pr(t_ls *tree)
{
	if (!tree)
		return ;
	//ft_printf("%c %c%c%c %s %s  %s %ld\t", tree->etype, tree->acc.ruser, tree->acc.wuser, tree->acc.xgrp, tree->uid_name, tree->path, tree->grp_name, tree->hlinks);
	ft_printf("%s", tree->mtime);
	//ft_printf("%d\n", tree->which);
	//ft_printf("%s : \t", tree->name);
	//ft_printf("%ld bytes\n", tree->size);
	if (tree->left)
		tree_pr(tree->left);
	if (tree->right)
		tree_pr(tree->right);
}

int			get_mtime(struct stat stp, t_ls *new)
{
	ft_bzero(new->mtime, NAME_MAX);
	ft_strcpy(new->mtime, ctime(&stp.st_mtime));
	return (1);
}

int			get_size(struct stat stp, t_ls *new)
{
	new->size = stp.st_size;
	return (1);
}

int			get_grp_name(struct stat stp, t_ls *new)
{
	struct group *grp;
	ft_bzero(new->grp_name, NAME_MAX);
	grp = getgrgid(stp.st_gid);
	ft_strcpy(new->grp_name, grp->gr_name);
	return (1);

}

int			get_uid_name(struct stat stp, t_ls *new)
{
	struct passwd *pwd;
	pwd = getpwuid(stp.st_uid);
	ft_strcpy(new->uid_name, pwd->pw_name);
	return (1);
}


static int	entry_opt_add(t_ls *new, t_ls **tree, int (* cmp)(char *, char *))
{
	t_ls *tmpTree = *tree;
	t_ls *tmpNode;
	int diff = 0;

	if (!tmpTree)
	{
		*tree = new;
		return (1);
	}
	while (tmpTree)
	{
		tmpNode = tmpTree;		//each time we move to next node in tree, set the ADDRESS of tmpNode equal to address of tmpTree. (now it's current with tmpTree).
		if ((diff = cmp(new->mtime, tmpTree->mtime)) > 0)
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

static int	entry_add(t_ls *new, t_ls **tree)
{
	t_ls *tmpTree = *tree;
	t_ls *tmpNode;

	if (!tmpTree)
	{
		*tree = new;
		return (1);
	}
	while (tmpTree)
	{
		tmpNode = tmpTree;		//each time we move to next node in tree, set the ADDRESS of tmpNode equal to address of tmpTree. (now it's current with tmpTree).
		if (new->path[0] > tmpTree->path[0])
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


int		count_links(struct stat stp, t_ls *new)
{
	new->hlinks = stp.st_nlink;
	return (1);
}



int		get_access(struct stat stp, t_ls *new)
{
	new->acc.ruser = (stp.st_mode & S_IRUSR) ? 'r' : '-';
	new->acc.wuser = (stp.st_mode & S_IWUSR) ? 'w' : '-';
	new->acc.xuser = (stp.st_mode & S_IXUSR) ? 'x' : '-';
	new->acc.rgrp = (stp.st_mode & S_IRGRP) ? 'r' : '-';
	new->acc.wgrp = (stp.st_mode & S_IWGRP) ? 'w' : '-';
	new->acc.xgrp = (stp.st_mode & S_IXGRP) ? 'x' : '-';
	new->acc.roth = (stp.st_mode & S_IROTH) ? 'r' : '-';
	new->acc.woth = (stp.st_mode & S_IWOTH) ? 'w' : '-';
	new->acc.xoth = (stp.st_mode & S_IXOTH) ? 'x' : '-';
	return (1);
}

int		get_type(struct stat stp, char *path, struct dirent *dp, t_ls *new)
{
	(void)path;
	(void)dp;
	if (S_ISREG(stp.st_mode))
		new->etype = '-';
	else if (S_ISDIR(stp.st_mode))
		new->etype = 'd';
	else if (S_ISCHR(stp.st_mode))
		new->etype = 'c';
	else if (S_ISBLK(stp.st_mode))
		new->etype = 'b';
	else if (S_ISFIFO(stp.st_mode))
		new->etype = 'p';
	else if (S_ISLNK(stp.st_mode))
		new->etype = 'l';
	else if (S_ISSOCK(stp.st_mode))
		new->etype = 's';
	else
	{
		ft_printf("No mode type found; aborting.\n");
		return (0);
	} 
	get_access(stp, new);
	count_links(stp, new);
	get_uid_name(stp, new);
	get_grp_name(stp, new);
	get_size(stp, new);
	get_mtime(stp, new);
	return(1);
}

int		stat_init(struct stat stp, char *path, struct dirent *dp, t_ls *new)
{
	get_type(stp, path, dp, new);
	return (1);
}

int		new_entry(struct stat stp, char *path, struct dirent *dp, t_ls **tree)
{
	int sort_time = 1;
	static int which = 1;
	if (!(path || dp || tree))
		return (0);
	t_ls *new;
	new = malloc(sizeof(t_ls));
	ft_bzero(new->uid_name, NAME_MAX);
	ft_bzero(new->grp_name, NAME_MAX);
	if (!(stat_init(stp, path, dp, new)))
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

	if (!sort_time)
		entry_add(new, tree);
	else
		entry_opt_add(new, tree, &ft_ustrcmp);
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
    ft_printf("------ > s : %s\n\n", s);

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
				//printf("Running lstat\n");
				lstat(path, &ltp);
				new_entry(ltp, path, dp, tree);
			}
			else
				new_entry(stp, path, dp, tree);
		}
		if (S_ISDIR(stp.st_mode) && !ft_strequ(dp->d_name, ".") && !ft_strequ(dp->d_name, ".."))
			rec_check(path, tree);
    }
    closedir(dir);
    return (0);
}


int		main(int ac, char **av)
{
	t_ls *tree;
	tree = NULL;
	if (ac != 2)
	{
		printf("handle multiple inputs soon....\n");
		return (0);
	}
	rec_check(av[1], &tree);
	tree_pr(tree);
	



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
