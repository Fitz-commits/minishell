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

/*
**	Skip all the first "-n"
**	if we have -n turn the flag at 1
**  putstr all the args
**  if the flag isn't 1 write \n
*/

int		ft_echo(t_mshl *m)
{
	int		i;
	short	flag;

	i = 1;
	flag = 0;
	if (m->nb_args > 1 && m->args[1]) 
	{
		while (m->args[i] && !ft_strcmp(m->args[i], "-n"))
			i++;
		flag = (i > 1) ? 1 : 0;
		while (m->args[i])
		{
			ft_putstr_fd(m->args[i], 1);
			if (i < m->nb_args - 1)
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	return (1);
}