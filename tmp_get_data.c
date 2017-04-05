# include "ft_ls.h"

char		*ft_strexclude(char *orig, char *excl)
{
	char *s;
	size_t olen;
	size_t exclen;

	olen = ft_strlen(orig);
	exclen = ft_strlen(excl);
	s = ft_strsub(orig, 0, olen - exclen);
	return (s);
}

int			get_color(t_ls *new, t_opt *e)
{
	if (e->ug)
	{
		if (new->etype == 'd')
			ft_strcpy(new->color.fg, FG_BLU);
		else if (new->etype == '-' && (new->acc.xuser == 'x' || new->acc.xgrp == 'x' || new->acc.xoth == 'x'))
			ft_strcpy(new->color.fg, FG_RED);
		else if (new->etype == 'l')
			ft_strcpy(new->color.fg, FG_PNK);
	}
	return (1);
}

int			get_size(t_ls *new, struct stat *stp)
{
	new->blkct = stp->st_blocks;
	new->hlinks = stp->st_nlink;
	if (ft_strequ(new->name, ".") || ft_strequ(new->name, ".."))
		new->is_rel = 1;
	else
		new->is_rel = 0;
	if (new->etype == 'c' || new->etype == 'b')
	{
		new->maj = major(stp->st_rdev);
		new->min = minor(stp->st_rdev);
	}
	else
		new->size = stp->st_size;
	return (1);
}

int			get_uidgrp(t_ls *new, struct stat *stp)
{
	struct passwd *pwd;
	struct group *grp;

	ft_bzero(new->grp_name, NAME_MAX);
	ft_bzero(new->uid_name, NAME_MAX);
	grp = getgrgid(stp->st_gid);
	pwd = getpwuid(stp->st_uid);
	ft_strcpy(new->grp_name, grp->gr_name);
	ft_strcpy(new->uid_name, pwd->pw_name);
	return (1);
}

int			get_access(t_ls *new, struct stat *stp)
{

	new->acc.ruser = (stp->st_mode & S_IRUSR) ? 'r' : '-';
	new->acc.wuser = (stp->st_mode & S_IWUSR) ? 'w' : '-';
	new->acc.xuser = (stp->st_mode & S_IXUSR) ? 'x' : '-';
	new->acc.rgrp = (stp->st_mode & S_IRGRP) ? 'r' : '-';
	new->acc.wgrp = (stp->st_mode & S_IWGRP) ? 'w' : '-';
	new->acc.xgrp = (stp->st_mode & S_IXGRP) ? 'x' : '-';
	new->acc.roth = (stp->st_mode & S_IROTH) ? 'r' : '-';
	new->acc.woth = (stp->st_mode & S_IWOTH) ? 'w' : '-';
	new->acc.xoth = (stp->st_mode & S_IXOTH) ? 'x' : '-';
	if (stp->st_mode & S_ISUID)
		new->acc.xuser = new->acc.xuser == '-' ? 'S' : 's';
	if (stp->st_mode & S_ISGID)
		new->acc.xgrp = new->acc.xgrp == '-' ? 'S' : 's';
	return (1);
}

// int			get_dir_size(t_dir *cwd, t_ls *new)
// {
// 	cwd->n += new->blkct;
// 	return(1);
// }

// 	if ()
// 	get_dir_size(cwd, new);

int			get_type(t_opt *e, t_ls *new, struct stat *stp)
{
	if (S_ISREG(stp->st_mode))
		new->etype = '-';
	else if (S_ISDIR(stp->st_mode))
		new->etype = 'd';
	else if (S_ISCHR(stp->st_mode))
		new->etype = 'c';
	else if (S_ISBLK(stp->st_mode))
		new->etype = 'b';
	else if (S_ISFIFO(stp->st_mode))
		new->etype = 'p';
	else if (S_ISLNK(stp->st_mode))
		new->etype = 'l';
	else if (S_ISSOCK(stp->st_mode))
		new->etype = 's';
	else
	{
		ft_printf("No mode type found; aborting.\n");
		return (0);
	}
	get_access(new, stp);
	get_uidgrp(new, stp);
	get_size(new, stp);

	get_mtime(*stp, new, e);
	get_color(new, e);
	return(1);
}