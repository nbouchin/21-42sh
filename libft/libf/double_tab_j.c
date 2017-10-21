/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_tab_j.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 12:13:23 by zadrien           #+#    #+#             */
/*   Updated: 2017/02/20 13:56:37 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

int		double_tab_j(char **tab, int p)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (p == 0)
	{
		while (tab[0][i])
		{
			if (tab[0][i] == '*')
				j++;
			i++;
		}
	}
	else
	{
		while (tab[1][i])
		{
			if (tab[1][i] == '*')
				j++;
			i++;
		}
	}
	return (j);
}
