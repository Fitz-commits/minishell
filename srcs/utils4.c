/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 23:14:08 by marvin            #+#    #+#             */
/*   Updated: 2020/11/05 23:14:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	itaob(int a, char **buff)
{
	int j;
	char *buf;

	buf = *buff;
	j = size(a); 
	buf[j] = 0;
	j -= 1;
	while(j >= 0)
	{
		buf[j--] = (a % 10) + 48;
		a = a / 10;
	}
}

int		reat_crval(t_mshl *m, int i)
{
	m->rvalue = i;
	itaob(i, &m->crvalue);
	return (0);
}

int		find_equ(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	**tabdup(char **tab)
{
	int		i;
	int		len;
	char	**newtab;

	i = 0;
	len = tablen(tab);
	if (!(newtab = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (i <= len)
		newtab[i++] = NULL;
	i = 0;
	while (i < len)
	{
		if(!(newtab[i] = strdup(tab[i])))
		{
			free_tab(newtab, 0, 1);
			return (NULL);
		}
		i++;
	}
	return (newtab);
}

void	sort_tab(char **tab)
{
	int i;
	int len;
	int loop;
	char *tmp;

	loop = 1;
	len = tablen(tab);
	while (loop)
	{
		loop = 0;
		i = 0;
		while (i < len - 1)
		{
			if (ft_strncmp(tab[i], tab[i + 1], find_equ(tab[i])) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				loop = 1; 
			}
			i++;
		} 
	}
}
