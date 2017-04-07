#include "ft_ls.h"

void	tree_del(t_ls *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		tree_del(tree->left);
	if (tree->right)
	{
		if (tree->left)
			free(tree->left);
		tree_del(tree->right);
	}
	free(tree);
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