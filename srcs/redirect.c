/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 12:28:49 by chris             #+#    #+#             */
/*   Updated: 2020/11/07 23:21:44 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** This function looks for redirection
** 1 is equal to input redirection
** 2 is equal to output redirection
** 3 is equal to output redirection >>
** 4 is equal to pipe
**      which means redirecting output of first command into
** input of next command
*/

int			check_red(t_mshl *m, int red)
{
	if (m->redir == 5)
		return (4);
	while (m->args[m->progr] && !red)
	{
		red = is_redir(m->args[m->progr]);
		if (qr_line(m))
			return (-1);
		if (red && (!m->args[m->progr + 1] || (m->progr == 0 &&
		!ft_strcmp(m->args[m->progr], "|")) || (is_redir(m->args[m->progr + 1])
		&& ft_strcmp(m->args[m->progr + 1], ">"))))
			return (err_redir(m));
		if (!red)
			m->cpargs[m->curs++] = m->args[m->progr];
		m->progr++;
	}
	if (red == 2 && m->args[m->progr] && !ft_strcmp(m->args[m->progr], ">"))
	{
		if (!(m->args[m->progr + 1]) || is_redir(m->args[m->progr + 1]))
			return (err_redir(m));
		red = 3;
		m->progr++;
	}
	return (red);
}

int			set_progr_tabl(t_mshl *m)
{
	int i;

	i = 0;
	while (m->args[i])
		i++;
	m->progr = i;
	return (0);
}

int			init_ptfr(int (*pt_f[6])(t_mshl*))
{
	pt_f[0] = set_progr_tabl;
	pt_f[1] = set_stdin;
	pt_f[2] = set_stdout;
	pt_f[3] = set_stdouta;
	pt_f[4] = set_apipes;
	pt_f[5] = set_bpipes;
	return (0);
}

int			handle_cpargs(t_mshl *m, int (*pt_fr[6])(t_mshl *m))
{
	while ((m->nb_args > m->progr && m->args[m->progr]) || m->cpargs[0])
	{
		if ((m->redir == 0 || m->redir == 4) && (errno || m->err))
			handle_error(m);
		else if (errno || m->err)
			reat_crval(m, 0);
		else
			reat_crval(m, 0);
		if (((m->redir = check_red(m, 0))) == -1)
			break ;
		if (m->redir >= 0 && m->redir <= 6)
			if (pt_fr[m->redir](m))
				break ;
		if ((m->redir == 5 || m->redir == 0) && !m->err && !errno)
		{
			choice_command(m);
			reset_cpargs(m);
		}
		if (m->redir != 5 && m->redir != 4)
			waiter(m);
	}
	return (EXIT_SUCCESS);
}

int			set_stdior(t_mshl *m)
{
	int		(*pt_fr[6])(t_mshl*);

	init_ptfr(pt_fr);
	if (!(m->cpargs = malloc(sizeof(char*) * (m->nb_args + 1))))
		m->nb_args = 0;
	reset_cpargs(m);
	handle_cpargs(m, pt_fr);
	if (errno || m->err)
		handle_error(m);
	else
		reat_crval(m, 0);
	return (EXIT_SUCCESS);
}
