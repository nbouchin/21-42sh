/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 18:06:32 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/15 13:05:13 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			bs(char *str, int i, int opt)
{
	int		count;

	count = 0;
	if (opt & CSQ)
		return (0);
	while (i && str[--i] == '\\')
		count++;
	if ((count % 2))
		return (1);
	return (0);
}

static void	count_quote(t_cmdl *cmdl)
{
	int		i;

	i = -1;
	while (cmdl->line.str[++i])
	{
		if (cmdl->line.str[i] == '\'' && (!(cmdl->opt & (CSQ | CDQ))) &&
				!bs(cmdl->line.str, i, cmdl->opt))
			cmdl->opt |= CSQ;
		else if (cmdl->line.str[i] == '"' && (!(cmdl->opt & (CSQ | CDQ))) &&
				!bs(cmdl->line.str, i, cmdl->opt))
			cmdl->opt |= CDQ;
		else if (cmdl->line.str[i] == '\'' && (cmdl->opt & CSQ) &&
				!bs(cmdl->line.str, i, cmdl->opt))
			cmdl->opt &= ~(CSQ);
		else if (cmdl->line.str[i] == '"' && (cmdl->opt & CDQ) &&
				!bs(cmdl->line.str, i, cmdl->opt))
			cmdl->opt &= ~(CDQ);
	}
}

int			check_quote(t_cmdl *cmdl)
{
	count_quote(cmdl);
	if ((cmdl->opt & (CSQ | CDQ)))
	{
		cmdl->opt &= ~(CPIPE | COR | CAND);
		regular_print(&cmdl->line, cmdl->line.buf,
			cmdl->line.cur - cmdl->line.pr, 0);
		cmdl->line.pr = (cmdl->opt & CSQ ?
		write(2, "\nquote> ", 8) - 1 : write(2, "\ndquote> ", 9) - 1);
		return ((cmdl->line.cur = cmdl->line.pr) ? 1 : 1);
	}
	return (0);
}
