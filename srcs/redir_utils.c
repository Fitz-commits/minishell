/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:32:39 by chris             #+#    #+#             */
/*   Updated: 2020/11/07 12:07:37 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			qr_line(t_mshl *m)
{
	char *temp;

	if (check_quotes(m->args[m->progr]))
	{
		if (!(temp = remove_quotes(m->args[m->progr], 0)))
			return (EXIT_FAILURE);
		else
			m->args[m->progr] = temp;
	}
	return (EXIT_SUCCESS);
}

int			err_redir(t_mshl *m)
{
	set_err(m, 2, 0, "Parsing error");
	return (-1);
}

int			reset_cpargs(t_mshl *m)
{
	if (m->cpargs)
		ft_bzero(m->cpargs, (sizeof(char*) * (m->nb_args + 1)));
	m->curs = 0;
	return (1);
}

int			is_redir(char *line)
{
	if (!ft_strcmp(line, "<"))
		return (1);
	else if (!ft_strcmp(line, ">"))
		return (2);
	else if (!ft_strcmp(line, "|"))
		return (5);
	else if (!ft_strcmp(line, ";"))
		return (5);
	else
		return (0);
}
