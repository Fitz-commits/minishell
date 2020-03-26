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

char	**ft_append(char **tab, char *str)
{
	char	**new_tab;
	int		i;

	i = tablen(tab);
	if (str)
		i += 1;
	if (!(new_tab = malloc((i + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	if (tab)
		while (tab[i])
		{
			new_tab[i] = ft_strdup(tab[i]);
			i++;
		}
	if (str)
	{
		new_tab[i] = ft_strdup(str);
		i++;
	}	
	new_tab[i] = NULL;
	return (new_tab);
}