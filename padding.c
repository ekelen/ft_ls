#include "ft_ls.h"

static int		init_pad(t_dir *cwd, t_ls *ls, t_opt *e)
{
	if (!ls)
		return(0);
	if (ls->left)
		init_pad(cwd, ls->left, e);
	if (e->l)
	{

		if (ft_numlen(ls->hlinks) >= cwd->pad->lnk)
			cwd->pad->lnk = ft_numlen(ls->hlinks); // + 1
		if (ft_strlen(ls->uid_name) >= cwd->pad->own)
			cwd->pad->own = ft_strlen(ls->uid_name); // + 1
		if (ft_strlen(ls->grp_name) >= cwd->pad->grp)
			cwd->pad->grp = ft_strlen(ls->grp_name); // + 2
		if (ls->etype == 'b' || ls->etype == 'c')
		{
			if (ft_numlen(ls->size) >= cwd->pad->size)
				cwd->pad->size = ft_numlen(ls->size); // + 2
			if (ft_numlen(ls->min) >= cwd->pad->min)
				cwd->pad->min = ft_numlen(ls->min);
			if (ft_numlen(ls->maj) >= cwd->pad->maj)
				cwd->pad->maj = ft_numlen(ls->maj);
			if (cwd->pad->size <= cwd->pad->maj + cwd->pad->min + 1)
				cwd->pad->size = cwd->pad->maj + cwd->pad->min + 1;
		}
		else
		{
			if (ft_numlen(ls->size) >= cwd->pad->size)
			cwd->pad->size = ft_numlen(ls->size); // + 2
		}
	}
	if (ls->right)
		init_pad(cwd, ls->right, e);
	return (1);
}	

int				get_padding(t_dir *cwd, t_ls *ls, t_opt *e)
{
	if (!(cwd->pad = malloc(sizeof(t_pad))))
	{
		error("malloc error");
		exit(-1);
	}
	cwd->pad->ext = 1;
	cwd->pad->lnk = 0;
	cwd->pad->own = 0;
	cwd->pad->grp = 0;
	cwd->pad->size = 0;
	cwd->pad->mon = 4;
	cwd->pad->dat = 3;
	cwd->pad->timyr = 5;
	cwd->pad->min = 0;
	cwd->pad->maj = 0;
	init_pad(cwd, ls, e);
	return (1);
}