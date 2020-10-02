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

/*
** TODO verifier que nb args = nb args du cpargs
** TODO echo >  doit renvoyer une error  -bash: syntax error near unexpected token `newline'
** TODO echo blabla > directory lancer une erreur
*/

int		ft_echo(t_mshl *m)
{
	int		i;
	short	flag;

	i = 1;
	flag = 0;
	if (m->nb_cpargs > 1 && m->cpargs[1]) 
	{
		while (m->cpargs[i] && !ft_strcmp(m->cpargs[i], "-n"))
			i++;
		flag = (i > 1) ? 1 : 0;
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