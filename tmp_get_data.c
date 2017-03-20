# include "ft_ls.h"

// int			get_parentchild(t_ls *new)
// {
// 	if (ft_strequ(new->name, ".") || ft_strequ(new->name, ".."))
// 		new->parentchild = 1;
// 	else
// 		new->parentchild = 0;
// 	return (1);
// }

// int			get_color(t_ls *new)
// {
// 	if (new->etype == 'd')
// 		ft_strcpy(new->color.fg, FG_BLUE);
// 	else if (new->etype == '-' && (new->acc.xuser == 'x' || new->acc.xgrp == 'x' || new->acc.xoth == 'x'))
// 		ft_strcpy(new->color.fg, FG_RED);
// 	else if (new->etype == 'l')
// 		ft_strcpy(new->color.fg, FG_MAGENTA);
// 	return (1);
// }

// int			color_init(t_ls *new)
// {
// 	ft_strcpy(new->color.bg, BG_DEFAULT);
// 	ft_strcpy(new->color.fg, FG_DEFAULT);
// 	get_color(new);
// 	return (1);
// }


// int			get_mtime(struct stat stp, t_ls *new)
// {
// 	new->hmtime = stp.st_mtime;
// 	ft_bzero(new->mtime, NAME_MAX);
// 	ft_strcpy(new->mtime, ctime(&stp.st_mtime));
// 	return (1);
// }

// int			get_size(struct stat stp, t_ls *new)
// {
// 	new->size = stp.st_size;
// 	return (1);
// }

// int			get_grp_name(struct stat stp, t_ls *new)
// {
// 	struct group *grp;
// 	ft_bzero(new->grp_name, NAME_MAX);
// 	grp = getgrgid(stp.st_gid);
// 	ft_strcpy(new->grp_name, grp->gr_name);
// 	return (1);

// }

// int			get_uid_name(struct stat stp, t_ls *new)
// {
// 	struct passwd *pwd;
// 	pwd = getpwuid(stp.st_uid);
// 	ft_strcpy(new->uid_name, pwd->pw_name);
// 	return (1);
// }

// int			count_links(struct stat stp, t_ls *new)
// {
// 	new->hlinks = stp.st_nlink;
// 	return (1);
// }

// int			get_access(struct stat stp, t_ls *new)
// {
// 	new->acc.ruser = (stp.st_mode & S_IRUSR) ? 'r' : '-';
// 	new->acc.wuser = (stp.st_mode & S_IWUSR) ? 'w' : '-';
// 	new->acc.xuser = (stp.st_mode & S_IXUSR) ? 'x' : '-';
// 	new->acc.rgrp = (stp.st_mode & S_IRGRP) ? 'r' : '-';
// 	new->acc.wgrp = (stp.st_mode & S_IWGRP) ? 'w' : '-';
// 	new->acc.xgrp = (stp.st_mode & S_IXGRP) ? 'x' : '-';
// 	new->acc.roth = (stp.st_mode & S_IROTH) ? 'r' : '-';
// 	new->acc.woth = (stp.st_mode & S_IWOTH) ? 'w' : '-';
// 	new->acc.xoth = (stp.st_mode & S_IXOTH) ? 'x' : '-';
// 	return (1);
// }


int			get_type(struct stat stp, char *path, struct dirent *dp, t_ls *new)
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
	// get_access(stp, new);
	// count_links(stp, new);
	// get_uid_name(stp, new);
	// get_grp_name(stp, new);
	// get_size(stp, new);
	// get_mtime(stp, new);
	// 	color_init(new);
	// 	get_parentchild(new);

	return(1);
}