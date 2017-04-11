# include "ft_ls.h"

static void			get_color_2(t_ls *new)
{
	if (new->etype == '-')
	{
	 if (ft_strchr("sS", new->acc.xuser))
	 {
	 	ft_strcpy(new->color.fg, FG_BLK);
	 	ft_strcpy(new->color.bg, FG_RED);
	 }
	 else if (ft_strchr("sS", new->acc.xgrp))
	 {
	 	ft_strcpy(new->color.fg, FG_BLK);
	 	ft_strcpy(new->color.bg, FG_CYN);
	 }
	 else if (new->acc.xuser == 'x')
	 	ft_strcpy(new->color.fg, FG_RED);
	}
	else if (new->etype == 'd')
	{
		if (new->acc.xoth == 't')
		{
			ft_strcpy(new->color.fg, FG_BLK);
	 		ft_strcpy(new->color.bg, FG_GRN);
		}
		else if (new->acc.xoth == 'T')
		{
			ft_strcpy(new->color.fg, FG_BLK);
			ft_strcpy(new->color.fg, FG_YEL);
		}
		else
			ft_strcpy(new->color.fg, FG_BLU);
	}
	return ;
}


int			get_color(t_ls *new, t_opt *e)
{
	if (e->ug)
	{
		ft_strcpy(new->color.fg, FG_RESET);
		ft_strcpy(new->color.bg, BG_RESET);
		if (new->etype == 'l')
			ft_strcpy(new->color.fg, FG_PNK);
		else if (new->etype == 's')
			ft_strcpy(new->color.fg, FG_GRN);
		else if (new->etype == 'p')
			ft_strcpy(new->color.fg, FG_YEL);
		else if (new->etype == 'b')
		{
			ft_strcpy(new->color.fg, FG_BLU);
			ft_strcpy(new->color.bg, BG_CYN);
		}
		if (new->etype == 'c')
		{
			ft_strcpy(new->color.fg, FG_BLU);
			ft_strcpy(new->color.bg, BG_YEL);
		}
		else
			get_color_2(new);
		return (1);
	}
	return(0);
}