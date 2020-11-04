/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:50:00 by marvin            #+#    #+#             */
/*   Updated: 2020/05/13 17:50:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_varname(char *var)
{
	int i;

	i = 0;
	if (!ft_strlen(var))
		return (9);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (9); //Not a valid identifier
		i++;
	}
	return (0);
}

int		del_varenv(t_mshl *m, int j)
{
	char	**nenv;
	int		len;
	int		i;
	int		k;

	i = 0;
	k = 0;
	len = tablen(m->cenv);
	if (!(nenv = (char **)malloc(sizeof(char *) * len)))
		return (3); //Memory Error
	while (m->cenv[i])
	{
		if (i != j)
		{
			if (!(nenv[k] = ft_strdup(m->cenv[i])))
				return (free_tab(nenv, 3, 1));
			k++;
		}
		i++;
	}
	nenv[k] = NULL;
	free_tab(m->cenv, 0, 1);
	m->cenv = nenv;
	return (0);
}

int		ft_unset(t_mshl *m)
{
	int i;
	int j;

	i = 0;
	if (m->nb_args > 1)
	{
		while (m->args[++i])
		{
			if (!check_varname(m->args[i]))
			{
				j = 0;
				while (m->cenv[j])
				{
					if (!ft_strncmp(m->cenv[j], m->args[i], until_dquotes(m->cenv[j]))
						&& !ft_strncmp(m->cenv[j], m->args[i], ft_strlen(m->args[i])))
					{
						del_varenv(m, j);
						break ;
					}
					j++;
				}
			}
			else
			{
				set_err(m, 1, 3, "unset", m->args[i], "not a valid identifier");
				ft_putendl_fd(m->err_to_print, 2);
				m->err = -10;
			}
			
		}
	}
	return (1);
}
