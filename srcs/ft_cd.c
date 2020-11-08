/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 23:34:32 by marvin            #+#    #+#             */
/*   Updated: 2020/11/08 13:21:14 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			set_oldpwd(t_mshl *m, int i, int j)
{
	char *tempc;
	char buffer[PATH_MAX];

	ft_bzero(buffer, PATH_MAX);
	ft_strcpy(buffer, getvar(m, "PWD"));
	if (i != -1 && j != -1)
	{
		if (!(tempc = pair_value_key(buffer, "OLDPWD")))
			return (set_err(m, 1, 0, strerror(ENOMEM)));
		free(m->cenv[i]);
		m->cenv[i] = tempc;
	}
	else if (i == -1 && j != -1)
	{
		if (!(tempc = pair_value_key(getvar(m, "PWD"), "OLDPWD")))
			return (set_err(m, 1, 0, strerror(ENOMEM)));
		if (!(m->cenv = ft_append(m, tempc)))
			return (set_err(m, 1, 0, strerror(ENOMEM)));
	}
	return (EXIT_SUCCESS);
}

int			set_pwd(t_mshl *m, char buffer[1024], int j)
{
	char *tempc;

	if (j != -1)
	{
		if (!(tempc = pair_value_key(buffer, "PWD")))
			return (set_err(m, 1, 0, strerror(ENOMEM)));
		free(m->cenv[j]);
		m->cenv[j] = tempc;
	}
	else
	{
		if (!(tempc = pair_value_key(buffer, "PWD")))
			return (set_err(m, 1, 0, strerror(ENOMEM)));
		if (!(m->cenv = ft_append(m, tempc)))
			return (set_err(m, 1, 0, strerror(ENOMEM)));
	}
	return (EXIT_SUCCESS);
}

int			set_del_pwd(t_mshl *m, int i, int j)
{
	if (j == -1)
	{
		if (i != -1)
			if (del_varenv(m, i))
				return (set_err(m, 1, 0, strerror(ENOMEM)));
	}
	else
	{
		if ((set_oldpwd(m, i, j)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			change_pwd(t_mshl *m)
{
	int		i;
	int		j;
	char	buffer[PATH_MAX];

	i = find_env(m->cenv, "OLDPWD");
	j = find_env(m->cenv, "PWD");
	ft_bzero(buffer, PATH_MAX);
	if (!(getcwd(buffer, PATH_MAX)))
	{
		errno = 0;
		if (set_oldpwd(m, i, j))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (set_del_pwd(m, i, j))
		return (EXIT_FAILURE);
	if (set_pwd(m, buffer, j))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			ft_cd(t_mshl *m)
{
	if (!m->cpargs[1])
		return (go_home(m));
	if (!m->cpargs[1][0])
	{
		chdir(".");
		return (change_pwd(m));
	}
	if (check_dperm(m, m->cpargs[1]))
		return (EXIT_FAILURE);
	if ((chdir(m->cpargs[1])) == -1)
		return (set_err(m, 1, 2, "cd", m->cpargs[1], strerror(errno)));
	return (change_pwd(m));
}
