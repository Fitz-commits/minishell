/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:37:41 by chris             #+#    #+#             */
/*   Updated: 2020/11/08 14:41:38 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			find_env_arg(char **env, char *arg)
{
	int	len_arg;
	int i;

	i = 0;
	len_arg = 0;
	while (arg[len_arg] != '=')
		len_arg++;
	while (env[i])
	{
		if (!ft_strncmp(arg, env[i], len_arg))
			return (i);
		i++;
	}
	return (-1);
}

/*
** format the key and the value to put in cenv
*/

int			parse_varname(char *str)
{
	int		i;

	i = 0;
	if (!ft_strlen(str))
		return (NOT_VALID_ID);
	if ((str[i] >= 48 && str[i] <= 57) || str[i] == '=')
		return (NOT_VALID_ID);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (NOT_VALID_ID);
		i++;
	}
	if (!str[i])
		return (-1);
	return (EXIT_SUCCESS);
}

static int	printexp(t_mshl *m)
{
	char	**tab;
	int		i;
	int		equ;

	i = -1;
	if (!(tab = tabdup(m->cenv)))
		return (EXIT_FAILURE);
	sort_tab(tab);
	while (tab[++i])
	{
		equ = 0;
		ft_putstr_fd("declare -x ", m->tstdout);
		while (tab[i][equ] != '=' && tab[i][equ])
			equ++;
		equ++;
		write(m->tstdout, tab[i], equ);
		ft_putchar_fd('\"', m->tstdout);
		if (!ft_strcmp(&tab[i][equ], "\""))
			ft_putstr_fd("\\", m->tstdout);
		ft_putstr_fd(&tab[i][equ], m->tstdout);
		ft_putchar_fd('\"', m->tstdout);
		ft_putchar_fd('\n', m->tstdout);
	}
	free_tab(tab, 0, 1);
	return (EXIT_SUCCESS);
}

static int	export_append(t_mshl *m, int i)
{
	int		temp;
	char	*tempc;

	if ((temp = find_env_arg(m->cenv, m->cpargs[i])) == -1)
	{
		if (!(tempc = ft_strdup(m->cpargs[i])))
			return (ENOMEM);
		if (!(m->cenv = ft_append(m, tempc)))
			return (ENOMEM);
	}
	else
	{
		if (!(tempc = ft_strdup(m->cpargs[i])))
			return (ENOMEM);
		free(m->cenv[temp]);
		m->cenv[temp] = tempc;
	}
	return (EXIT_SUCCESS);
}

int			ft_export(t_mshl *m)
{
	int	i;
	int	ret;

	i = 1;
	if (m->nb_cpargs == 1)
	{
		if (printexp(m))
			return (set_err(m, 1, 0, strerror(ENOMEM)));
		return (EXIT_SUCCESS);
	}
	while (m->cpargs[i])
	{
		if ((ret = parse_varname(m->cpargs[i])) > 0)
			exp_error(m, i);
		else if (!ret)
		{
			if (export_append(m, i))
				return (set_err(m, 1, 0, strerror(ENOMEM)));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
