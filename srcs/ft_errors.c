/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:56:53 by chris             #+#    #+#             */
/*   Updated: 2020/11/08 13:11:57 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		reset_struct(t_mshl *m)
{
	m->nb_cpargs = 0;
	set_zpb(m);
	clear_std(m);
	close_pipes(m);
	clean_args(m);
	return (EXIT_SUCCESS);
}

int		main_error(t_mshl *m)
{
	handle_error(m);
	free_str(&m->reader, 0);
	free_str(&m->buff_cmd, 0);
	reset_struct(m);
	return (EXIT_SUCCESS);
}

int		exp_error(t_mshl *m, int i)
{
	set_err(m, 1, 3, "export", m->cpargs[i], "not a valid identifier");
	ft_putendl_fd(m->err_to_print, 2);
	m->err = -10;
	return (EXIT_SUCCESS);
}

int		handle_error(t_mshl *m)
{
	if (m->err != -10 && m->err != 4)
		ft_putendl_fd(m->err_to_print, 2);
	m->err = 0;
	errno = 0;
	return (EXIT_SUCCESS);
}
