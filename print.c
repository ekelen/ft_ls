#include "ft_ls.h"

// static int	ipad_pr(int print, size_t width, int align)
// {
// 	size_t i;

// 	i = 0;
// 	if (align)
// 		ft_printf("%d", (int)print);
// 	if (ft_numlen(print) < width)
// 	{
// 		while (ft_numlen(print) + i < width)
// 		{
// 			ft_putchar(' ');
// 			i++;
// 		}
// 	}
// 	if (!align)
// 		ft_printf("%d", (int)print);
// 	ft_putchar(' ');
// 	return (0);
// }

// static int	cpad_pr(char *print, size_t width, int align)
// {
// 	size_t i;

// 	i = 0;
// 	if (align)
// 		ft_printf("%s", print);
// 	if (ft_strlen(print) < width)
// 	{
// 		while (ft_strlen(print) + i < width)
// 		{
// 			ft_putchar(' ');
// 			i++;
// 		}
// 	}
// 	if (!align)
// 		ft_printf("%s", print);
// 	ft_putchar(' ');
// 	return (0);
// }

// static int	print_id(t_ls *tree, t_dir *cwd)
// {
// 	cpad_pr(tree->uid_name, cwd->pad->own, 1);
// 	ft_putchar(' ');
// 	cpad_pr(tree->grp_name, cwd->pad->grp, 1);
// 	ft_putchar(' ');
// 	return (1);
// }

static int	tree_lpr(t_ls *tree, t_dir *cwd, t_opt *e)
{
	if (e->l)
	{
		ft_printf("%c%c%c%c%c%c%c%c%c%c ", tree->etype, tree->acc.ruser, tree->acc.wuser, tree->acc.xuser, tree->acc.rgrp, tree->acc.wgrp, tree->acc.xgrp, tree->acc.roth, tree->acc.woth, tree->acc.xoth);
		// ipad_pr(tree->hlinks, cwd->pad->lnk, 0);
		// print_id(tree, cwd);
		// ipad_pr(tree->size, cwd->pad->size, 0);
		print_time(tree, cwd);
		return (1);
	}
	return (0);
}

void	open_rec(t_ls *entry, t_dir cwd, t_opt *e)
{
	if (!entry)
		return ;
	if (entry->left)
		open_rec(entry->left, cwd, e);
	//ft_printf("%s%s%s", tree->color.fg, tree->name, FG_RESET);
	//ft_printf("%s\n", tree->linkname);
	if (entry->etype == 'd' && !entry->parentchild)
	{
		ft_printf("Found directory: %s\n", entry->path);
		init_open(entry->path, e, cwd);
	}
	
	if (entry->right)
		open_rec(entry->right, cwd, e);
}

void	tree_pr(t_ls *entry, t_dir cwd, t_opt *e)
{
	if (!entry)
		return ;
	if (entry->left)
		tree_pr(entry->left, cwd, e);
	tree_lpr(entry, &cwd, e);
	ft_printf("%s%s%s", entry->color.fg, entry->name, FG_RESET);
	ft_printf("%s\n", entry->linkname);
	//ft_printf("dir path : %s    e-> l : %d   entry->name : %s\n", cwd.path, e->l, entry->name);
	if (entry->right)
		tree_pr(entry->right, cwd, e);
}

// void	tree_pr(t_ls *tree, t_dir *cwd, t_opt *e)
// {
// 	if (!tree)
// 		return ;
// 	if (tree->left)
// 		tree_pr(tree->left, cwd, e);
// 	tree_lpr(tree, cwd, e);
// 	ft_printf("%s%s%s", tree->color.fg, tree->name, FG_RESET);
// 	ft_printf("%s\n", tree->linkname);
// 	if (tree->right)
// 		tree_pr(tree->right, cwd, e);
// }

// void meta_pr(t_dir *tree, t_opt *e)
// {
// 	if (!tree)
// 		return ;
// 	if (tree->left)	
// 		meta_pr(tree->left, e);
// 	ft_printf("\n%s\n", tree->path);
// 	tree_pr(tree->entries, tree, e);
// 	if (tree->right)
// 		meta_pr(tree->right, e);
// }