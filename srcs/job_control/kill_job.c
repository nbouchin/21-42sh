/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 18:55:00 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/07 08:17:57 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		kill_job(t_ast **ast, t_env **env)
{
	t_ast	*tmp;
	(void)env;
	if (*ast)
	{
		tmp = (*ast)->left;
		/* ft_putast(tmp); */
	}
	return (1);
}
