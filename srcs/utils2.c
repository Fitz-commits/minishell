/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:49:37 by marvin            #+#    #+#             */
/*   Updated: 2020/03/26 16:49:37 by marvin           ###   ########.fr       */
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
