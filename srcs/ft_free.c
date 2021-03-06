/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:24:56 by chris             #+#    #+#             */
/*   Updated: 2020/11/07 11:31:14 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**free_tabs(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

void		free_all(t_mshl *m)
{
	free(m->crvalue);
	if (m->args)
		free_tab(m->args, 1, 1);
	if (m->cpargs)
		free(m->cpargs);
	if (m->reader)
		free(m->reader);
	if (m->buff_cmd)
		free(m->buff_cmd);
	free_tab(m->cenv, 1, 1);
}

int			free_str(char **str, int ret)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (ret);
}

/*
** if the code is 0 just free the pointer of the tab
** else if the code is 1 the function free ALL the tab
*/

int			free_tab(char **tab, int ret, char code)
{
	int i;

	i = 0;
	if (tab)
	{
		if (code)
		{
			while (tab[i])
			{
				free(tab[i]);
				i++;
			}
		}
		free(tab);
	}
	tab = NULL;
	return (ret);
}
