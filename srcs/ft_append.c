/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 20:06:09 by marvin            #+#    #+#             */
/*   Updated: 2020/03/26 20:06:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_append(t_mshl *m, char *str)
{
	char	**new_tab;
	int		i;

	i = tablen(m->cenv);
	if (str)
		i += 1;
	if (!(new_tab = malloc((i + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	if (m->cenv)
		while (m->cenv[i])
		{
			new_tab[i] = m->cenv[i];
			i++;
		}
    free(m->cenv);
	if (str)
	{
		new_tab[i] = str;
		i++;
	}	
	new_tab[i] = NULL;
	return (new_tab);
}