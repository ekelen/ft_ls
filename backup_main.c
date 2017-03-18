#include "ft_ls.h"
#include <stdio.h> // DELETE



static void	tree_pr(t_ls *tree)
{
	if (!tree)
		return ;
	ft_printf("%s\n", tree->name);
	if (tree->left)
		tree_pr(tree->left);
	if (tree->right)
		tree_pr(tree->right);
}

static int	s_dir_info(t_ls *new, t_ls **tree)
{
	t_ls *tmpTree = *tree;
	t_ls *tmpNode;

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

int		get_new(struct stat stp, char *s, struct dirent *dp, t_ls **tree)
{
	t_ls *new;
	new = malloc(sizeof(t_ls));
	(void)stp;
	(void)s;
	

	ft_strcpy(new->name, dp->d_name);
	new->d_ino = dp->d_ino;
	new->right = NULL;
	new->left = NULL;
	s_dir_info(new, tree);
	return (1);
}


void	rec_check(char *s, t_ls **tree)
{
	DIR 			*dir;
    struct dirent	*dp;
    struct stat		stp;

	dir = opendir(s);
	while (dir) 
	{
	    if ((dp = readdir(dir)) != NULL) 
	    {
	    	get_new(stp, s, dp, tree);
	    	if (stat(s, &stp) < 0)
			{
				ft_printf("Stat problem\n");
				return ;
			}
			if (S_ISDIR(stp.st_mode))
			{
				printf("s recursive : %s%s\n", s, dp->d_name);
				rec_check((ft_strjoin(s, dp->d_name)), tree);
			}
		   
	    }
	    else 
	   	{
	   		tree_pr(*tree);
	        closedir(dir);
	        return ;
	    }
	}

}


int		main(int ac, char **av)
{
	t_ls *tree;
	tree = NULL;
	if (ac != 2)
	{
		printf("handle multiple inputs soon....\n");
		return (0);
	}
	rec_check(av[1], &tree);
	// DIR *dirp;
 //    struct dirent *dp;
 //    t_ls 	*tree;
 //    tree = NULL;
 //    if (ac > 2)
 //    	return (0);
	// dirp = opendir(av[1]);
	// //rec_check(av[1], dp, &tree);
	// while (dirp) 
	// {
	//     if ((dp = readdir(dirp)) != NULL) 
	//     {
	//     	get_new(av[1], dp, &tree);	
	//     }
	//     else 
	//    	{
	//    		tree_pr(tree);
	//         closedir(dirp);
	//         return (0);
	//     }
	// }



 
 





	   //struct stat stp;
    // if(stat(av[1],&stp) < 0)    
    //     return 1;
 
    // printf("Information for %s\n",s);
    // printf("---------------------------\n");
    // printf("File Size: \t\t%lld bytes\n",stp.st_size);
    // printf("Number of Links: \t%d\n",stp.st_nlink);
    // printf("File inode: \t\t%lld\n",stp.st_ino);
 
    // printf("File Permissions: \t");
    // printf( (S_ISDIR(stp.st_mode)) ? "d" : "-");
    // printf( (stp.st_mode & S_IRUSR) ? "r" : "-");
    // printf( (stp.st_mode & S_IWUSR) ? "w" : "-");
    // printf( (stp.st_mode & S_IXUSR) ? "x" : "-");
    // printf( (stp.st_mode & S_IRGRP) ? "r" : "-");
    // printf( (stp.st_mode & S_IWGRP) ? "w" : "-");
    // printf( (stp.st_mode & S_IXGRP) ? "x" : "-");
    // printf( (stp.st_mode & S_IROTH) ? "r" : "-");
    // printf( (stp.st_mode & S_IWOTH) ? "w" : "-");
    // printf( (stp.st_mode & S_IXOTH) ? "x" : "-");
    // printf("\n\n");
 
    // printf("The file %s a symbolic link\n", (S_ISLNK(stp.st_mode)) ? "is" : "is not");












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
