/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 14:08:34 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/02 17:39:19 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		mod_env(t_env **env, char *path, char *save)
{
	t_env		*tmp;

	tmp = lst_at(env, "OLDPWD");
	if (tmp)
	{
		ft_strdel(&tmp->value);
		if (lst_at(env, "PWD"))
			tmp->value = ft_strdup(lst_at(env, "PWD")->value);
		else
			tmp->value = ft_strdup(save);
	}
	tmp = lst_at(env, "PWD");
	if (tmp)
	{
		ft_strdel(&tmp->value);
		tmp->value = ft_strdup(path);
	}
}

static int		chdirectory(char **path, int opt, char *arg)
{
	struct stat		st;
	char			buff[1024];
	char			*bs;
	int				i;

	i = 0;
	if (lstat((*path), &st) == -1)
		return (fd_printf(2, "cd: no such file or directory: %@\n", arg));
	if (S_ISDIR(st.st_mode) || (i = S_ISLNK(st.st_mode)))
	{
		if ((access((*path), R_OK)) == -1)
			return (fd_printf(2, "cd: permission denied: %@\n", arg));
		if (chdir((*path)) == -1)
			return (fd_printf(2, "cd: %@:not a directoryn", arg));
		if (i && opt == 1)
		{
			readlink((*path), buff, 1024);
			bs = ft_strrchr((*path), '/');
			*(bs + 1) = 0;
			(*path) = ft_strjoinf((*path), buff, 1);
		}
	}
	else
		return (fd_printf(2, "cd: %@: not a directory\n", arg));
	return (0);
}

static int		get_opt(char **arg, int *i, int *opt)
{
	int		j;

	(*i) = 0;
	while (arg[(*i)] && arg[(*i)][0] == '-')
	{
		j = 0;
		if (arg[(*i)][0] == '-' && ((arg[(*i)][1] == '-' && arg[(*i)][2] == 0)
		|| arg[(*i)][1] == 0))
			return (0);
		while (arg[(*i)][++j])
		{
			if (arg[(*i)][j] == 'P')
				(*opt) = 1;
			else if (arg[(*i)][j] == 'L')
				(*opt) = 2;
			else
				return (fd_printf(2, "cd: -%c: invalid option\n",
				arg[(*i)][j]));
		}
		(*i) += 1;
	}
	return (0);
}

static void		build_path(char **path, char *arg, t_env **env)
{
	char	**rp;
	int		i;
	int		len;

	i = -1;
	(*path) = ft_strdup(lst_at(env, "PWD")->value);
	(*path)[ft_strlen(*path) - 1] == '/' ?
			(*path)[ft_strlen(*path) - 1] = 0 : 0;
	rp = ft_strsplit(arg, '/');
	if (rp)
	{
		while (rp[++i])
		{
			len = 0;
			if (rp[i][0] == '.' && rp[i][1] == '.' && rp[i][2] == 0)
			{
				len = ft_strlen((*path));
				while ((*path)[--len])
					if ((*path)[len] == '/')
						break ;
				(*path)[len + (len ? 0 : 1)] = 0;
			}
			else
				(*path) = (*path)[ft_strlen((*path))] == '/' ? ft_strjoinf((*path),
				rp[i], 3) : ft_strjoinf(ft_strjoinf((*path), "/", 1), rp[i], 1);
		}
		ft_free(rp, NULL, 1);
	}
	else
		fd_printf(2, "cd: HOME not set\n");
}

static void		cd_get_path(t_env **lstenv, char *arg, char **path)
{
	char	*tmp;

	tmp = NULL;
	if (arg)
		arg[ft_strlen(arg) - 1] == '/' ? arg[ft_strlen(arg) - 1] = 0 : 0;
	if (!arg)
	{
		if (lst_at(lstenv, "HOME"))
			(*path) = ft_strdup(lst_at(lstenv, "HOME")->value);
	}
	else if (arg[0] == 0)
		(*path) = ft_strdup("/");
	else if (arg[0] == '-' && arg[1] == 0)
	{
		if (lst_at(lstenv, "OLDPWD"))
			(*path) = ft_strdup(lst_at(lstenv, "OLDPWD")->value);
		else
			fd_printf(2, "cd: OLDPWD not set\n");
	}
	else if ((!(tmp = ft_strstr(arg, ".."))) ||
	         (tmp && tmp[2] != 0 && tmp[2] != '/'))
	{
		if (arg[0] == '/')
			(*path) = ft_strdup(arg);
		else if (arg[0] == '.' && arg[1] == 0)
		{
			if (lst_at(lstenv, "PWD"))
				(*path) = ft_strdup(lst_at(lstenv, "PWD")->value);
			else
				fd_printf(2, "cd: PWD not set\n");
		}
		else
		{
			if (lst_at(lstenv, "PWD"))
			{
				tmp = lst_at(lstenv, "PWD")->value;
				(*path) = tmp[ft_strlen(tmp) - 1] == '/' ? ft_strjoin(tmp, arg)
						: ft_strjoinf(ft_strjoin(tmp, "/"), arg, 1);
			}
			else
			{
				tmp = ft_memalloc(sizeof(char) * 1024);
				tmp = getwd(*path);
				(*path )= tmp[ft_strlen(tmp) - 1] == '/' ? ft_strjoin(tmp, arg)						 : ft_strjoinf(ft_strjoin(tmp, "/"), arg, 1);
				ft_putendl(*path);
			}
		}
	}
	!(*path) ? build_path(path, arg, lstenv) : 0;
}

static int		check_arg(int len, char *arg, t_env **lstenv)
{
	if (len == 2)
		return (fd_printf(2, "cd: string not in pwd: %s\n", arg));
	else if (len > 2)
		return (fd_printf(2, "cd: too many arguments\n"));
	if (*lstenv && (!(lst_at(lstenv, "PWD"))) && arg && arg[0] == '-' && arg[1] == 0)
		return (fd_printf(2, "cd: OLDPWD not set\n"));
	else if (*lstenv && (!(lst_at(lstenv, "OLDPWD"))) && arg && arg[0] == '-' && arg[1] == 0)
		return (fd_printf(2, "cd: OLDPWD not set\n"));
	else if (*lstenv && (!(lst_at(lstenv, "HOME"))) && arg && arg[0] == '~')
		return (fd_printf(2, "cd: HOME not set\n"));
	return (0);
}

int				ft_cd(t_ast **ast, t_env **env)
{
	char	**targ;
	char	*save;
	char	*path;
	int		opt;
	int		i;

	
	opt = 2;
	i = 0;
	path = NULL;
	save = ft_memalloc(sizeof(char) * 1024);
	save = getwd(save);
	(*ast)->right ? io_seq(&(*ast)->right->right) : 0;
	targ = creat_arg_env(&(*ast)->left->right);
	if ((targ && get_opt(targ, &i, &opt)) ||
	    (check_arg(i ? ft_tablen(targ + i) : 0, i ? targ[i] : NULL, env)))
	{
		ft_free(targ, &save, 1);
		return (0);
	}
	cd_get_path(env, targ ? targ[i] : NULL, &path);
	if (chdirectory(&path, opt, targ ? targ[i] : NULL))
	{
		ft_free(targ, &path, 3);
		ft_strdel(&save);
		return (0);
	}
	mod_env(env, path, save);
	ft_free(targ, &path, 3);
	ft_strdel(&save);
	return (1);
}
