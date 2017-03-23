#include "ft_ls.h"


static int	sort_size(t_ls *new, t_ls **tree)
{
	t_ls *tmpTree = *tree;
	t_ls *tmpNode;

	if (!tmpTree)
	{
		ft_printf("Some kind of tree error\n");
		return (0);
	}
	while (tmpTree)
	{
		tmpNode = tmpTree;
		if (new->size < tmpTree->size)
		{
			tmpTree = tmpTree->right;
			if (!tmpTree)
			{
				tmpNode->right = new;
			}
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



static int	sort_ascii(t_ls *new, t_ls **tree)
{
	t_ls *tmpTree;
	t_ls *tmpNode;
	int diff;

	tmpTree = *tree;
	diff = 0;
	if (!tmpTree)
	{
		ft_printf("Some kind of tree error\n");
		return (0);
	}
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

static int	sort_time(t_ls *new, t_ls **tree)
{
	t_ls *tmpTree = *tree;
	t_ls *tmpNode;

	if (!tmpTree)
	{
		ft_printf("Some kind of tree error\n");
		return (0);
	}
	while (tmpTree)
	{
		tmpNode = tmpTree;
		if (new->time->mmod < tmpTree->time->mmod)
		{
			tmpTree = tmpTree->right;
			if (!tmpTree)
				tmpNode->right = new;
		}
		else
		{
			if (new->time->mmod == tmpTree->time->mmod)
			{
				if (new->time->mnsec < tmpTree->time->mnsec)
				{		
					tmpTree = tmpTree->right;
					if (!tmpTree)
						tmpNode->right = new;
				}
				else if (new->time->mnsec > tmpTree->time->mnsec)
				{
					tmpTree = tmpTree->left;
					if (!tmpTree)
						tmpNode->left = new;
				}
				else
				{
					if ((ft_ustrcmp(new->name, tmpTree->name)) > 0)
					{

						tmpTree = tmpTree->right;
						if (!tmpTree)
							tmpNode->right = new;
					}
					else
					{
						tmpTree = tmpTree->left;
						if (!tmpTree)
							tmpNode->left = new;
					}
				}
			}
			else
			{
				tmpTree = tmpTree->left;
				if (!tmpTree)
					tmpNode->left = new;
			}
		}
	}
	return (1);
}


int	sort_entries(t_ls *new, t_ls **tree, t_opt *e)
{
	if (!*tree)
	{
		*tree = new;
		return (1);
	}
	if (e->us)
		sort_size(new, tree);
	else if (e->t)
		sort_time(new, tree);
	else
		sort_ascii(new, tree);
	return (1);
}