/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 20:49:22 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/15 13:05:59 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void			ccp_case(t_cmdl *cmdl, int save)
{
	cmdl->line.cur = write(1, cmdl->line.str, ft_strlen(cmdl->line.str))
	+ cmdl->line.pr;
	home(cmdl);
	end(cmdl);
	while (cmdl->line.cur > save)
		arrow_left(cmdl);
}

static void		comp_case(t_cmdl *cmdl, int save)
{
	cmdl->line.cur = write(1, cmdl->line.str, ft_strlen(cmdl->line.str))
	+ cmdl->line.pr;
	while (cmdl->line.cur > save)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		cmdl->line.cur--;
	}
	if (cmdl->opt & CCOMP)
	{
		cmdl->opt &= ~CCMODE;
		display_comp(cmdl, &cmdl->comp, 0);
	}
}

static void		search_hist_case(t_cmdl *cmdl, int save)
{
	t_his	*his;

	his = findcmdl(cmdl->line.str, 0, 2);
	cmdl->line.cur = 22 + ft_strlen(cmdl->line.str) +
	(his ? ft_strlen(his->cmdl) : 0);
	fd_printf(2, "(reverse-i-search)`%s': %s", cmdl->line.str,
	his ? his->cmdl : "");
	while (cmdl->line.cur > save)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		cmdl->line.cur--;
	}
}

void			resize_win(t_cmdl *cmdl, int save)
{
	if (cmdl->opt & (CAND | COR | CPIPE | CSQ | CSQ))
		return ;
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	get_win_data(cmdl);
	print_prompt();
	if (cmdl->opt & CCP)
		ccp_case(cmdl, save);
	else if (cmdl->opt & CCOMP)
		comp_case(cmdl, save);
	else if (cmdl->opt & CHIS_S)
		search_hist_case(cmdl, save);
	else if (!cmdl->opt)
	{
		cmdl->line.cur = write(1, cmdl->line.str, ft_strlen(cmdl->line.str))
		+ cmdl->line.pr;
		while (cmdl->line.cur > save)
			arrow_left(cmdl);
	}
}
