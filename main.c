#include "ft_ls.h"
#include <stdio.h> // DELETE


void	print_tree_data(t_ls *tree)
{
	if (!tree)
		return ;
	ft_printf("%d", tree->data);
	if (tree->left)
	{
		ft_printf("data->left : ");
		print_tree_data(tree->left);
	}
	if (tree->right)
	{
		ft_printf("data->right : ");
		print_tree_data(tree->right);
	}
}


void	test_add(t_ls **tree, int data)
{
	if (!(tree))
		printf("No *tree\n");
	t_ls *tmpTree = *tree;
	t_ls *tmpNode;				//WHY ME?

	t_ls *new;
	new = malloc(sizeof(t_ls));
	new->data = data;
	new->right = NULL;
	new->left = NULL;
	if (!tmpTree)
	{
		*tree = new;
		return ;
	}
	printf("root node (*tree) data : %d\n", (*tree)->data); // saved
	while (tmpTree)
	{
		tmpNode = tmpTree;		//each time we move to next node in tree, set the ADDRESS of tmpNode equal to address of tmpTree. (now it's current with tmpTree).
		if (data > tmpTree->data)
		{
			tmpTree = tmpTree->right;	//tmpNode is now one node behind tmpTree.
			if (!tmpTree)
			{
				tmpNode->right = new;	//tmpNode->right (at same address of tmpTree) now holds data.
				//printf("\n -----> %d\n", tmpNode->right->data);
			}
		}
		else
		{
			tmpTree = tmpTree->left;
			if (!tmpTree)
			{
				tmpNode->left = new;
			}
		}
	}
	return ;
}

int		main(int ac, char **av)
{
	DIR *dir;
    struct dirent *dp;
    if (ac > 2)
    	return (0);
    if ((dir = opendir (av[1])) == NULL) {
        ft_printf("Couldn't open directory.\n");
        exit (1);
    }
    while ((dp = readdir (dir)) != NULL) {
    	ft_printf("Found %s\n", dp->d_name);
    		closedir(dir);
    }


   

	t_ls *tree;
	tree = NULL;
	test_add(&tree, 4);
	test_add(&tree, 10);
	test_add(&tree, 15);
	test_add(&tree, 3);
	test_add(&tree, 2);

	print_tree_data(tree);
	ft_printf("Test\n");

	//-l, -R, -a, -r and -t
	//l = "long"
	//-a = include things with a dot
	//-t == sort by time
	//-r == reverse order
	//-R == recursively list subdirectories encountered

	//BONUS TODO:
	//-h (uses unit instead of size)
	//-m (stream output across the page, separated by commas)
	//-p (add a slash after each directory found
	//-S sort files by size
	//-o same as -l but without group id
	//-G colorized output
	//invent your own (ask if want to list ? search directory ?)
	//-A list all entries except . and ..

	
	return (0);
}
