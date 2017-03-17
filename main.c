#include "ft_ls.h"
#include <stdio.h> // DELETE


void	print_tree_data(t_ls *tree)
{
	if (!tree)
		return ;
	ft_printf("Printing name : \n");
	ft_printf("%s", tree->name);
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


// void	test_add(t_ls **tree, int data)
// {
// 	if (!(tree))
// 		printf("No *tree\n");
// 	t_ls *tmpTree = *tree;
// 	t_ls *tmpNode;

// 	t_ls *new;
// 	new = malloc(sizeof(t_ls));
// 	new->data = data;
// 	new->right = NULL;
// 	new->left = NULL;
// 	if (!tmpTree)
// 	{
// 		*tree = new;
// 		return ;
// 	}
// 	printf("root node (*tree) data : %d\n", (*tree)->data); // saved
// 	while (tmpTree)
// 	{
// 		tmpNode = tmpTree;		//each time we move to next node in tree, set the ADDRESS of tmpNode equal to address of tmpTree. (now it's current with tmpTree).
// 		if (data > tmpTree->data)
// 		{
// 			tmpTree = tmpTree->right;	//tmpNode is now one node behind tmpTree.
// 			if (!tmpTree)
// 			{
// 				tmpNode->right = new;	//tmpNode->right (at same address of tmpTree) now holds data.
// 				//printf("\n -----> %d\n", tmpNode->right->data);
// 			}
// 		}
// 		else
// 		{
// 			tmpTree = tmpTree->left;
// 			if (!tmpTree)
// 			{
// 				tmpNode->left = new;
// 			}
// 		}
// 	}
// 	return ;
// }


static int	dir_info(struct dirent *dp, t_ls **tree)
{
	t_ls *tmpTree = *tree;
	t_ls *tmpNode;

	t_ls *new;
	new = malloc(sizeof(t_ls));
	ft_strcpy(new->name, dp->d_name);
	//printf("new->name : %s\n", new->name);
	new->right = NULL;
	new->left = NULL;

	if (!tmpTree)
	{
		*tree = new;
		return (1);
	}
	


	while (tmpTree)
	{
		tmpNode = tmpTree;		//each time we move to next node in tree, set the ADDRESS of tmpNode equal to address of tmpTree. (now it's current with tmpTree).
		if (new->name[0] > tmpTree->name[0])
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
	printf("tree : %s\n", (*tree)->name);
	// ft_strcpy(ls.name, dp->d_name);
	return (1);
}

int		main(int ac, char **av)
{
	DIR *dirp;
    struct dirent *dp;
    t_ls 	*tree;
    tree = NULL;
    if (ac > 2)
    	return (0);
	dirp = opendir(av[1]);
	while (dirp) 
	{
	    if ((dp = readdir(dirp)) != NULL) 
	    {
	    	dir_info(dp, &tree);
	    }
	    else 
	   	{
	        closedir(dirp);
	        return (0);
	    }
	}
	print_tree_data(tree);

    // if (!(stat(av[1], &sb)))
    // {
    // 	ft_printf("Couldn't get stat struct for dir.\n");
    // 	exit(1);
    // }

// if (d_type == DT_UNKNOWN)
//     		check_type_macros(sb.st_mode);
//     if S_ISREG(sb.st_mode)
// // is it a regular file?

// S_ISDIR(m)

// // directory?

// S_ISCHR(m)

// // character device?

// S_ISBLK(m)

// // block device?

// S_ISFIFO(m)

// // FIFO (named pipe)?

// S_ISLNK(m)

// // symbolic link? (Not in POSIX.1-1996.)

// S_ISSOCK(m)

// socket? (Not in POSIX.1-1996.)


   

	// t_ls *tree;
	// tree = NULL;
	// test_add(&tree, 4);
	// test_add(&tree, 10);
	// test_add(&tree, 15);
	// test_add(&tree, 3);
	// test_add(&tree, 2);


	//ft_printf("Test\n");

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
