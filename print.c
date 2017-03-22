#include "ft_ls.h"

static int	ipad_pr(int print, size_t width, int align)
{
	size_t i;

	i = 0;
	if (align)
		ft_printf("%d", (int)print);
	if (ft_numlen(print) < width)
	{
		while (ft_numlen(print) + i < width)
		{
			ft_putchar(' ');
			i++;
		}
	}
	if (!align)
		ft_printf("%d", (int)print);
	
	return (0);
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

static int	print_id(t_ls *tree, t_dir *cwd)
{
	cpad_pr(tree->uid_name, cwd->pad->own, 1);
	ft_putchar(' ');
	cpad_pr(tree->grp_name, cwd->pad->grp, 1);
	ft_putchar(' ');
	return (1);
}

int		print_name(t_ls *entry, t_opt *e, t_dir *cwd)
{
	int i;

	i = 0;
	if (e->ug)
		ft_printf("%s%s%s", entry->color.fg, entry->name, FG_RESET);
	else
		ft_printf("%s", entry->name);
	while (ft_strlen(entry->name) + i < cwd->pad->name)
	{
		ft_putchar(' ');
		i++;
	}
	if (entry->etype == 'l' && e->l)
		ft_printf("%s", entry->linkname);
	if (e->l)
		ft_putchar('\n');
	return (1);
}



static int	tree_lpr(t_ls *entry, t_dir *cwd, t_opt *e)
{
	(void)e;
	ft_printf("%c%c%c%c%c%c%c%c%c%c", entry->etype, entry->acc.ruser, entry->acc.wuser, entry->acc.xuser, entry->acc.rgrp, entry->acc.wgrp, entry->acc.xgrp, entry->acc.roth, entry->acc.woth, entry->acc.xoth);
	ft_printf("  ");
	ipad_pr(entry->hlinks, cwd->pad->lnk, 0);
    ft_putchar(' ');
	print_id(entry, cwd);
	ipad_pr(entry->size, cwd->pad->size, 0);
	print_time(entry, cwd);
	return (1);
}

void	tree_pr(t_ls *entry, t_dir cwd, t_opt *e)
{
	if (!entry)
		return ;
	if (entry->left)
		tree_pr(entry->left, cwd, e);
	if (e->l)
		tree_lpr(entry, &cwd, e);
	print_name(entry, e, &cwd);
	if (entry->right)
		tree_pr(entry->right, cwd, e);
}

void	tree_prrv(t_ls *entry, t_dir cwd, t_opt *e)
{
	if (!entry)
		return ;
	if (entry->right)
		tree_prrv(entry->right, cwd, e);
	if (e->l)
		tree_lpr(entry, &cwd, e);
	print_name(entry, e, &cwd);
	if (entry->left)
		tree_prrv(entry->left, cwd, e);
}