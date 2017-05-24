/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 12:42:25 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/24 13:53:15 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_var(t_env **env, char *var, char *value)
{
	t_env	*tmp;

	tmp = *env;
	if (var)
	{
		tmp->var = ft_strdup(var);
		if (value)
			tmp->value = ft_strdup(value);
		else
			ft_strdup("");
	}
}

void	add_env(t_env **env, char **arg)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = (t_env*)malloc(sizeof(t_env))))
		return ;
	tmp = tmp->next;
	add_var(&tmp, arg[0], arg[1]);
	tmp->next = NULL;

}

int		ft_setenv(t_ast **ast, t_env **env)
{
	int		i;
	char	**arg;

	arg = NULL;
	arg = creat_arg_env(&(*ast)->right);
	ft_putendl(arg[0]);
	ft_putendl(arg[1]);
	if ((i = countab(arg)) == 1 || i == 2)
	{
		add_env(env, arg);
		arg ? ft_freetab(arg) : 0;
		return (1);
	}
	else if (i > 2)
		ft_errormsg("21sh: ", "env: ", "Too many arguments.");
	else if (i == 0)
		ft_errormsg("21sh: ", "env: ", "Too few arguments.");
	arg ? ft_freetab(arg) : 0;
	return (0);
}