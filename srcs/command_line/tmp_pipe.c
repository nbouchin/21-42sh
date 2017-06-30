/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 17:10:08 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/30 17:55:19 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	tmp_pipe(int *p, int flag)
{
	static int	tmp[2];

	if (flag == 0)
	{
		tmp[0] = p[0];
		tmp[1] = p[1];
	}
	else if (flag == 1 && tmp[0] > -1)
	{
		p[0] = tmp[0];
		p[1] = tmp[1];
	}
	else
	{
		tmp[0] = -1;
		tmp[1] = -1;
		p[0] = tmp[0];
		p[1] = tmp[1];
	}
}
