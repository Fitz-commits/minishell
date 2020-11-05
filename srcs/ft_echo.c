/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 17:17:27 by marvin            #+#    #+#             */
/*   Updated: 2020/03/26 17:17:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_n(char *str)
{
	int i;

	i = 0;
	if (str[i] != '-')
		return (1);
	i++;
	while (str[i] == 'n')
		i++;
	if (!str[i])
		return (0);
	return (1);
}

int		ft_echo(t_mshl *m)
{
	int		i;
	short	flag;

	i = 1;
	flag = 0;
	if (m->nb_cpargs > 1 && m->cpargs[1]) 
	{
		while (m->cpargs[i] && !is_n(m->cpargs[i]))
			i++;
		if (i > 1)
			flag = 1;
		while (m->cpargs[i])
		{
			ft_putstr_fd(m->cpargs[i], m->tstdout);
			if (i < m->nb_cpargs - 1)
				ft_putchar_fd(' ', m->tstdout);
			i++;
		}
	}
	if (!flag)
		ft_putchar_fd('\n', m->tstdout);
    close_rp(m);
	return (0);
}
