/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:56:26 by chris             #+#    #+#             */
/*   Updated: 2020/11/07 10:56:27 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_n(char *str)
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

int			ft_echo(t_mshl *m)
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
