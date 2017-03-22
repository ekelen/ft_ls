#include "ft_ls.h"

static int		init_pad(t_dir *cwd, t_ls *ls, t_opt *e)
{
	if (ls->left)
		init_pad(cwd, ls->left, e);
	if (e->l)
	{
		if (ft_numlen(ls->hlinks) >= cwd->pad->lnk)
			cwd->pad->lnk = ft_numlen(ls->hlinks); // + 1
		if (ft_strlen(ls->uid_name) >= cwd->pad->own)
			cwd->pad->own = ft_strlen(ls->uid_name); // + 1
		if (ft_strlen(ls->grp_name) >= cwd->pad->grp)
			cwd->pad->grp = ft_strlen(ls->grp_name); // + 2
		if (ft_numlen(ls->size) >= cwd->pad->size)
			cwd->pad->size = ft_numlen(ls->size); // + 2
	}
	else
	{
		if (ft_strlen(ls->path) >= cwd->pad->name)
			cwd->pad->name = ft_strlen(ls->path);
	}
	if (ls->right)
		init_pad(cwd, ls->right, e);
	return (1);
}	


int				get_padding(t_dir *cwd, t_ls *ls, t_opt *e)
{
	cwd->pad = malloc(sizeof(t_pad));
	cwd->pad->acc = 10;
	cwd->pad->ext = 1;
	cwd->pad->lnk = 0;
	cwd->pad->own = 0;
	cwd->pad->grp = 0;
	cwd->pad->size = 0;
	cwd->pad->mon = 4;
	cwd->pad->dat = 3;
	cwd->pad->timyr = 5;
	cwd->pad->name = 0;
	init_pad(cwd, ls, e);
	return (1);
}



// -rwxr-xr-x   1 ekelen  october    4096 Nov  9 11:50 ._lib
// -rwxr-xr-x   1 ekelen  october    4096 Nov  9 11:50 ._locale
// -rw-r--r--   1 ekelen  october    4096 Nov  9 11:50 ._qt.conf
// -rw-r--r--   1 ekelen  october    4096 Nov  9 11:50 ._site.pyc
// -rw-r--r--@  1 ekelen  october    1589 Apr  9  2016 __boot__.py
// -rwxr-xr-x@  1 ekelen  october     559 Mar  3  2014 __error__.sh
// -rw-r--r--@  1 ekelen  october  143827 Apr  9  2016 anki.icns
// -rw-r--r--@  1 ekelen  october      87 Jun  1  2011 ankiqtmac.py
// -rw-r--r--@  1 ekelen  october   15269 Apr  9  2016 ankiweb.certs
// drwxr-xr-x@  2 ekelen  october    4096 Apr  9  2016 audio
// drwxr-xr-x@  2 ekelen  october    4096 Apr  9  2016 imageformats
// drwxr-xr-x@  3 ekelen  october    4096 Apr  9  2016 include
// drwxr-xr-x@  3 ekelen  october    4096 Apr  9  2016 lib
// drwxr-xr-x@ 59 ekelen  october    4096 Apr  9  2016 locale
// -rw-r--r--@  1 ekelen  october      63 Apr  9  2016 qt.conf
// -rw-r--r--@  1 ekelen  october    3380 Mar  3  2014 site.pyc

// Makefile	error.h		ft_catpath.o	ft_numlen.o	main.c		pad.o	print.o		time.o
// author		ft_abs.c	ft_ls		ft_ustrcmp.c	main.o		parse_args.c	printf		tmp_get_data.c
// color.h		ft_abs.o	ft_ls.h		ft_ustrcmp.o	options.h	parse_args.o	symlink.c	tmp_get_data.o
// env_pad.h	ft_catpath.c	ft_numlen.c	libft		pad.c	print.c		time.c