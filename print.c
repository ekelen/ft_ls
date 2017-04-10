#include "ft_ls.h"

static int	ipad_pr(size_t print, size_t width, size_t align)
{
	size_t i;

	i = 0;
	if (align)
		ft_printf("%zd", print);
	if (ft_numlen(print) < width)
	{
		while (ft_numlen(print) + i < width)
		{
			ft_putchar(' ');
			i++;
		}
	}
	if (!align)
		ft_printf("%zd", print);
	return (1);
}

static int	cpad_pr(char *print, size_t width, int align)
{
	size_t i;

	i = 0;
	if (align)
		ft_printf("%s", print);
	if (ft_strlen(print) < width)
	{
		while (ft_strlen(print) + i < width)
		{
			ft_putchar(' ');
			i++;
		}
	}
	if (!align)
		ft_printf("%s", print);
	ft_putchar(' ');
	return (0);
}

static int	print_id(t_opt *e, t_ls *tree, t_dir *cwd)
{
	if (!e->g)
	{
		cpad_pr(tree->uid_name, PAD.own, 1);
		ft_putchar(' ');
	}
	if (!e->o)
	{
		cpad_pr(tree->grp_name, PAD.grp, 1);
		ft_putchar(' ');
	}
	return (1);
}

static int	tree_lpr(t_ls *entry, t_dir *cwd, t_opt *e)
{
	ft_printf("%c%c%c%c%c%c%c%c%c%c", entry->etype, entry->acc.ruser, entry->acc.wuser, entry->acc.xuser, entry->acc.rgrp, entry->acc.wgrp, entry->acc.xgrp, entry->acc.roth, entry->acc.woth, entry->acc.xoth);
	if (entry->acl)
		ft_putchar(entry->acl);
	ft_putchar(' ');
	ipad_pr(entry->hlinks, PAD.lnk, 0);
    ft_putchar(' ');
	print_id(e, entry, cwd);
	if (ft_strchr("bc", entry->etype))
	{
		ipad_pr(entry->maj, PAD.maj, 0);
		ft_putchar(',');
		ipad_pr(entry->min, PAD.min, 0);
	}
	else
			ipad_pr(entry->size, PAD.size, 0);
	print_time(e, entry, cwd);
	return (1);
}

int		print_name(t_ls *entry, t_opt *e)
{
	int i;

	i = 0;
	if (e->ug)
	{
		ft_printf("%s%s%s", entry->color.fg, entry->name);
		if (e->p && entry->etype == 'd')
			ft_putchar('/');
		ft_printf("%s", FG_RESET);
	}
	else
	{
		ft_printf("%s", entry->name);
	}
	ft_strdel(&entry->name);
	if (entry->etype == 'l' && e->l)
		ft_printf(" -> %s", entry->linkname);
	if (e->p && entry->etype == 'd')
			ft_putchar('/');
	ft_putchar('\n');
	return (1);
}

static int		entry_pr(t_ls *entry, t_dir *cwd, t_opt *e)
{
	if (e->l)
		tree_lpr(entry, cwd, e);
	print_name(entry, e);
	return(1);
}

void	tree_pr(t_ls *entry, t_dir cwd, t_opt *e)
{
	if (!entry)
		return ;
	if (entry->left)
		tree_pr(entry->left, cwd, e);
	entry_pr(entry, &cwd, e);
	if (entry->right)
		tree_pr(entry->right, cwd, e);
}

void	tree_prrv(t_ls *entry, t_dir cwd, t_opt *e)
{
	if (!entry)
		return ;
	if (entry->right)
		tree_prrv(entry->right, cwd, e);
	entry_pr(entry, &cwd, e);
	if (entry->left)
		tree_prrv(entry->left, cwd, e);
}