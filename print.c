#include "ft_ls.h"

void	tree_pr(t_ls *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		tree_pr(tree->left);
	ft_printf("%c%c%c%c%c%c%c%c%c%c", tree->etype, tree->acc.ruser, tree->acc.wuser, tree->acc.xuser, tree->acc.rgrp, tree->acc.wgrp, tree->acc.xgrp, tree->acc.roth, tree->acc.woth, tree->acc.xoth);
	ft_printf("% ld\t%-s %s", tree->hlinks, tree->uid_name, tree->grp_name);
	ft_printf("\t%ld", tree->size);
	ft_printf("%s\t%s%s", tree->color.fg, tree->name, FG_RESET);
	ft_printf("%s", tree->linkname);
	
	ft_printf("\t%s%s%s", FG_RESET, tree->mtime, FG_RESET);
	if (tree->right)
		tree_pr(tree->right);
}

void meta_pr(t_dir *tree)
{
	if (!tree)
		return ;
	if (tree->left)	
		meta_pr(tree->left);
	ft_printf("\n%s\n", tree->path);
	tree_pr(tree->entries);
	if (tree->right)
		meta_pr(tree->right);
}