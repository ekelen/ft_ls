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
	ft_putchar(' ');
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

static int	print_hlinks(t_ls *tree, t_dir *cwd)
{
	ipad_pr(tree->hlinks, cwd->padding->lnk, 0);
	ft_putchar(' ');
	return (1);
}

static int	print_id(t_ls *tree, t_dir *cwd)
{
	cpad_pr(tree->uid_name, cwd->padding->own, 1);
	ft_putchar(' ');
	ft_putchar(' ');
	cpad_pr(tree->grp_name, cwd->padding->grp, 1);
	ft_putchar(' ');
	return (1);
}

static void	tree_pr(t_ls *tree, t_dir *cwd)
{
	(void)cwd;
	time_t current_time;
	current_time = time(0);

	if (!tree)
		return ;
	if (tree->left)
		tree_pr(tree->left, cwd);
	ft_printf("%c%c%c%c%c%c%c%c%c%c", tree->etype, tree->acc.ruser, tree->acc.wuser, tree->acc.xuser, tree->acc.rgrp, tree->acc.wgrp, tree->acc.xgrp, tree->acc.roth, tree->acc.woth, tree->acc.xoth);

	print_hlinks(tree, cwd);
	print_id(tree, cwd);
	ipad_pr(tree->size, cwd->padding->size, 0);
	print_time(tree, cwd);
	// ft_printf(" %s", tree->mmon);
	// ft_printf(" %s", tree->mdate);
	// ft_printf(" %s", tree->mhr);
	// ft_printf(" %s", tree->myr);
	ft_printf(" %s%s%s", tree->color.fg, tree->name, FG_RESET);
	ft_printf("%s\n", tree->linkname);
	if (tree->right)
		tree_pr(tree->right, cwd);
}

void meta_pr(t_dir *tree)
{
	if (!tree)
		return ;
	if (tree->left)	
		meta_pr(tree->left);
	ft_printf("\n%s\n", tree->path);
	tree_pr(tree->entries, tree);
	if (tree->right)
		meta_pr(tree->right);
}