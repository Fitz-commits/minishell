/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:49:37 by marvin            #+#    #+#             */
/*   Updated: 2020/11/07 20:36:49 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_for_dc(char **args)
{
	int		i;

	i = -1;
	if (!args)
		return (-1);
	while (args[++i])
		if (!ft_strcmp(args[i], ";"))
			return (i);
	return (-1);
}

int			clean_args(t_mshl *m)
{
	int		i;

	i = 0;
	if (m->cpargs)
		free(m->cpargs);
	m->cpargs = NULL;
	if (m->args)
	{
		while (m->args[i])
			free(m->args[i++]);
	}
	free(m->args);
	m->args = NULL;
	if (!m->buff_cmd)
		if (m->reader)
		{
			free(m->reader);
			m->reader = NULL;
		}
	return (0);
}

void		set_zpb(t_mshl *m)
{
	m->progr = 0;
	m->err = 0;
}

int			prep_rv(t_mshl *m)
{
	if (!(m->crvalue = malloc(sizeof(char) * 10)))
		return (EXIT_FAILURE);
	reat_crval(m, 0);
	return (0);
}

void		ft_init(t_mshl *m)
{
	ft_bzero(m->err_to_print, PATH_MAX + 1);
	m->args = NULL;
	m->cpargs = NULL;
	m->reader = NULL;
	m->nb_cpargs = 0;
	m->nb_args = 0;
	m->tstdin = 0;
	m->tstdout = 1;
	m->reader = NULL;
	m->redir = 0;
	m->rvalue = 0;
	m->buff_cmd = NULL;
	m->progr = 0;
	m->err = 0;
	zeroing_pipes(m);
	zeroing_process(m);
}
