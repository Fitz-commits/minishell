/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:50:00 by marvin            #+#    #+#             */
/*   Updated: 2020/11/07 11:34:03 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_varname(char *var)
{
	int i;

	i = 0;
	if (!ft_strlen(var))
		return (NOT_VALID_ID);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (NOT_VALID_ID);
		i++;
	}
	return (0);
}

int				del_varenv(t_mshl *m, int j)
{
	char	**nenv;
	int		len;
	int		i;
	int		k;

	i = 0;
	k = 0;
	len = tablen(m->cenv);
	if (!(nenv = (char **)malloc(sizeof(char *) * len)))
		return (ENOMEM);
	while (m->cenv[i])
	{
		if (i != j)
		{
			if (!(nenv[k] = ft_strdup(m->cenv[i])))
				return (free_tab(nenv, ENOMEM, 1));
			k++;
		}
		i++;
	}
	nenv[k] = NULL;
	free_tab(m->cenv, 0, 1);
	m->cenv = nenv;
	return (0);
}

static void		unset_loop(t_mshl *m, int i)
{
	int j;

	j = 0;
	while (m->cenv[j])
	{
		if (!ft_strncmp(m->cenv[j], m->cpargs[i], until_dquotes(m->cenv[j]))
			&& !ft_strncmp(m->cenv[j], m->cpargs[i], ft_strlen(m->cpargs[i])))
		{
			del_varenv(m, j);
			break ;
		}
		j++;
	}
}

int				ft_unset(t_mshl *m)
{
	int i;

	i = 0;
	if (m->nb_cpargs > 1)
	{
		while (m->cpargs[++i])
		{
			if (!check_varname(m->cpargs[i]))
				unset_loop(m, i);
			else
			{
				set_err(m, 1, 3, "unset", m->cpargs[i],
				"not a valid identifier");
				ft_putendl_fd(m->err_to_print, 2);
				m->err = -10;
			}
		}
	}
	return (EXIT_SUCCESS);
}
