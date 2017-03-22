#include "ft_ls.h"

int	sort_dirs_time(t_dir *new, t_dir **tree)
{
	t_dir *tmpTree = *tree;
	t_dir *tmpNode;

	while (tmpTree)
	{
		tmpNode = tmpTree;		//each time we move to next node in tree, set the ADDRESS of tmpNode equal to address of tmpTree. (now it's current with tmpTree).
		if (new->dir_meta->lastmod > tmpTree->dir_meta->lastmod)
		{
			tmpTree = tmpTree->right;	//tmpNode is now one node behind tmpTree.
			if (!tmpTree)
				tmpNode->right = new;	//tmpNode->right (at same address of tmpTree) now holds data
		}
		else
		{
			tmpTree = tmpTree->left;
			if (!tmpTree)
				tmpNode->left = new;
		}

	}
	return (1);
}

int	sort_dirs_ascii(t_dir *new, t_dir **tree)
{
	t_dir *tmpTree = *tree;
	t_dir *tmpNode;

	int diff;
	while (tmpTree)
	{
		tmpNode = tmpTree;		//each time we move to next node in tree, set the ADDRESS of tmpNode equal to address of tmpTree. (now it's current with tmpTree).
		if ((diff = ft_ustrcmp(new->path, tmpTree->path)) > 0)
		{
			tmpTree = tmpTree->right;	//tmpNode is now one node behind tmpTree.
			if (!tmpTree)
				tmpNode->right = new;	//tmpNode->right (at same address of tmpTree) now holds data
		}
		else
		{
			tmpTree = tmpTree->left;
			if (!tmpTree)
				tmpNode->left = new;
		}

	}
	return (1);
}

int		move_cwd(t_opt *e, t_dir *cwd, t_dir **root)
{
	t_dir *new;
	// if (e->l)
		get_padding(cwd, cwd->entries);
	// else
	// 	get_col_padding(cwd, cwd->entries);

	new = malloc(sizeof(t_dir));
	*new = *cwd;
	new->left = NULL;
	new->right = NULL;
	new->entries = cwd->entries;
	if (!(*root)) 
	{
		*root = new;
		return(1);
	}
	if (e->t)
		sort_dirs_time(new, root);
	else
		sort_dirs_ascii(new, root);
	return (1);
}












// static int	sort_dirs_ascii(t_dir *new, t_dir **tree)
// {
// 	t_dir *tmpTree = *tree;
// 	t_dir *tmpNode;

// 	int diff;
// 	while (tmpTree)
// 	{
// 		tmpNode = tmpTree;		//each time we move to next node in tree, set the ADDRESS of tmpNode equal to address of tmpTree. (now it's current with tmpTree).
// 		if ((diff = ft_ustrcmp(new->path, tmpTree->path)) > 0)
// 		{
// 			tmpTree = tmpTree->right;	//tmpNode is now one node behind tmpTree.
// 			if (!tmpTree)
// 				tmpNode->right = new;	//tmpNode->right (at same address of tmpTree) now holds data
// 		}
// 		else
// 		{
// 			tmpTree = tmpTree->left;
// 			if (!tmpTree)
// 				tmpNode->left = new;
// 		}

// 	}
// 	return (1);
// }