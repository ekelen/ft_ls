#include "ft_ls.h"

void	tree_del(t_ls *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		tree_del(tree->left);
	ft_strdel(&tree->name);
	ft_strdel(&tree->path);
	free(tree->time);
	free(tree);
	if (tree->right)
		tree_del(tree->right);
}

void	free_args(char **args, int i)
{
	while (i >= 0)
	{
		free(args[i]);
		i--;
	}
	free(args);
}