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

int			get_size(t_dir *cwd, t_ls *new)
{
	new->blkct = (new->stp)->st_blocks;
	cwd->n += new->blkct;
	new->hlinks = (new->stp)->st_nlink;
	if (ft_strequ(new->name, ".") || ft_strequ(new->name, ".."))
		new->is_rel = 1;
	else
		new->is_rel = 0;
	if (new->etype == 'c' || new->etype == 'b')
	{
		new->maj = major((new->stp)->st_rdev);
		new->min = minor((new->stp)->st_rdev);
	}
	else
		new->size = (new->stp)->st_size;
	return (1);
}

int			get_uidgrp(t_ls *new)
{
	struct passwd *pwd;
	struct group *grp;

	ft_bzero(new->grp_name, NAME_MAX);
	ft_bzero(new->uid_name, NAME_MAX);
	grp = getgrgid((new->stp)->st_gid);
	pwd = getpwuid((new->stp)->st_uid);
	ft_strcpy(new->grp_name, grp->gr_name);
	ft_strcpy(new->uid_name, pwd->pw_name);
	return (1);
}

int			get_access(t_ls *new)
{

	new->acc.ruser = ((new->stp)->st_mode & S_IRUSR) ? 'r' : '-';
	new->acc.wuser = ((new->stp)->st_mode & S_IWUSR) ? 'w' : '-';
	new->acc.xuser = ((new->stp)->st_mode & S_IXUSR) ? 'x' : '-';
	new->acc.rgrp = ((new->stp)->st_mode & S_IRGRP) ? 'r' : '-';
	new->acc.wgrp = ((new->stp)->st_mode & S_IWGRP) ? 'w' : '-';
	new->acc.xgrp = ((new->stp)->st_mode & S_IXGRP) ? 'x' : '-';
	new->acc.roth = ((new->stp)->st_mode & S_IROTH) ? 'r' : '-';
	new->acc.woth = ((new->stp)->st_mode & S_IWOTH) ? 'w' : '-';
	new->acc.xoth = ((new->stp)->st_mode & S_IXOTH) ? 'x' : '-';
	if ((new->stp)->st_mode & S_ISUID)
		new->acc.xuser = new->acc.xuser == '-' ? 'S' : 's';
	if ((new->stp)->st_mode & S_ISGID)
		new->acc.xgrp = new->acc.xgrp == '-' ? 'S' : 's';
	return (1);
}

int			get_type(t_opt *e, t_ls *new, t_dir *cwd)
{
	if (S_ISREG((new->stp)->st_mode))
		new->etype = '-';
	else if (S_ISDIR((new->stp)->st_mode))
		new->etype = 'd';
	else if (S_ISCHR((new->stp)->st_mode))
		new->etype = 'c';
	else if (S_ISBLK((new->stp)->st_mode))
		new->etype = 'b';
	else if (S_ISFIFO((new->stp)->st_mode))
		new->etype = 'p';
	else if (S_ISLNK((new->stp)->st_mode))
		new->etype = 'l';
	else if (S_ISSOCK((new->stp)->st_mode))
		new->etype = 's';
	else
	{
		ft_printf("No mode type found; aborting.\n");
		return (0);
	}
	get_access(new);
	get_uidgrp(new);
	get_size(cwd, new);
	get_mtime(*(new->stp), new, e);
	get_color(new, e);
	return(1);
}



