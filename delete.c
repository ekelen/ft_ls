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