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
		return (1); // ATTENTION ERROR CODE A MOFIDIER + FREE LES TRUCS ICI
	while (m->cenv[i] && i < j)
		nenv[k++] = m->cenv[i++];
	if (m->cenv[j])
	{
		i = j + 1;
		while (m->cenv[i])
			nenv[k++] = m->cenv[i++];
	}
	free_str(&m->cenv[j], 0);
	free_tab(m->cenv, 0, 0);
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
			j = 0;
			while (j >= 0 && m->cenv[j])
			{
				if (!ft_strncmp(m->cenv[j], m->args[i], until_dquotes(m->cenv[j]))
					&& !ft_strncmp(m->cenv[j], m->args[i], ft_strlen(m->args[i])))
				{
					del_varenv(m, j);
					j = -2;
				}
				j++;
			}
		}
	}
	return (1);
}