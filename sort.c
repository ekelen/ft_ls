#include "ft_ls.h"

static void	place_left(t_ls *new, t_ls **tt, t_ls *tn)
{
	(*tt) = (*tt)->left;
	if (!(*tt))
		tn->left = new;
}

static void	place_right(t_ls *new, t_ls **tt, t_ls *tn)
{
	(*tt) = (*tt)->right;
	if (!(*tt))
		tn->right = new;
}

static int	sort_size(t_ls *new, t_ls **tree)
{
	t_ls *tt = *tree;
	t_ls *tn;

	if (!tt)
		return (0);
	while (tt)
	{
		tn = tt;
		if (new->size > tt->size)
			place_right(new, &tt, tn);
		else if (new->size == tt->size \
			&& (ft_ustrcmp(new->name, tt->name)) > 0)
			place_right(new, &tt, tn);
		else
			place_left(new, &tt, tn);
	}
	return (1);
}

static int	sort_ascii(t_ls *new, t_ls **tree)
{
	t_ls *tt;
	t_ls *tn;

	tt = *tree;
	if (!tt)
		return (0);
	while (tt)
	{
		tn = tt;
		if ((ft_ustrcmp(new->path, tt->path)) > 0)
			place_right(new, &tt, tn);
		else
			place_left(new, &tt, tn);
	}
	return (1);
}



static int	sort_time(t_ls *new, t_ls **tree)
{
	t_ls *tt = *tree;
	t_ls *tn;
 
	if (!tt)
		return (0);
	while (tt)
	{
		tn = tt;
		if (new->MT < tt->MT)
			place_right(new, &tt, tn);
		else if (new->MT == tt->MT && new->MS < tt->MS)
			place_right(new, &tt, tn);
		else if (new->MT == tt->MT && new->MS == tt->MS \
			&& (ft_ustrcmp(new->name, tt->name)) > 0)
			place_right(new, &tt, tn);
		else
			place_left(new, &tt, tn);
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
	if (e->t)
	{
		sort_time(new,tree);
	}
	else if (e->us)
		sort_size(new, tree);
	else
		sort_ascii(new, tree);
	// else if (e->t)
	// 	sort_time(new, tree);
	//else
		
	return (1);
}





// static int	sort_size(t_ls *new, t_ls **tree)
// {
// 	t_ls *tt = *tree;
// 	t_ls *tn;

// 	if (!tt)
// 		return (0);
// 	while (tt)
// 	{
// 		tn = tt;
// 		if (new->size < tt->size)
// 		{
// 			tt = tt->right;
// 			if (!tt)
// 			{
// 				tn->right = new;
// 			}
// 		}
// 		else
// 		{
// 			tt = tt->left;
// 			if (!tt)
// 				tn->left = new;
// 		}
// 	}
// 	return (1);
// }

// static int	sort_ascii(t_ls *new, t_ls **tree)
// {
// 	t_ls *tt;
// 	t_ls *tn;

// 	tt = *tree;
// 	if (!tt)
// 		return (0);
// 	while (tt)
// 	{
// 		tn = tt;
// 		if ((ft_ustrcmp(new->path, tt->path)) > 0)
// 		{
// 			tt = tt->right;
// 			if (!tt)
// 				tn->right = new;
// 		}
// 		else
// 		{
// 			tt = tt->left;
// 			if (!tt)
// 				tn->left = new;
// 		}
// 	}
// 	return (1);
// }

// static int	sort_time(t_ls *new, t_ls **tree)
// {
// 	t_ls *tt = *tree;
// 	t_ls *tn;

// 	if (!tt)
// 		return (0);
// 	while (tt)
// 	{
// 		tn = tt;
// 		if (new->MT < tt->MT)
// 		{
// 			tt = tt->right;
// 			if (!tt)
// 				tn->right = new;
// 		}
// 		else
// 		{
// 			if (new->MT == tt->MT)
// 			{
// 				if (new->MS < tt->MS)
// 				{		
// 					tt = tt->right;
// 					if (!tt)
// 						tn->right = new;
// 				}
// 				else if (new->MS > tt->MS)
// 				{
// 					tt = tt->left;
// 					if (!tt)
// 						tn->left = new;
// 				}
// 				else
// 				{
// 					if ((ft_ustrcmp(new->name, tt->name)) > 0)
// 					{

// 						tt = tt->right;
// 						if (!tt)
// 							tn->right = new;
// 					}
// 					else
// 					{
// 						tt = tt->left;
// 						if (!tt)
// 							tn->left = new;
// 					}
// 				}
// 			}
// 			else
// 			{
// 				tt = tt->left;
// 				if (!tt)
// 					tn->left = new;
// 			}
// 		}
// 	}
// 	return (1);
// }


// int	sort_entries(t_ls *new, t_ls **tree, t_opt *e)
// {
// 	if (!*tree)
// 	{
// 		*tree = new;
// 		return (1);
// 	}
// 	if (e->us)
// 		sort_size(new, tree);
// 	else if (e->t)
// 		sort_time(new, tree);
// 	else
// 		sort_ascii(new, tree);
// 	return (1);
// }