/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:36:13 by chris             #+#    #+#             */
/*   Updated: 2020/11/07 12:17:19 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**  So ret is the value for $?
**  Option is if you need one or two or three things nothed
*/

int		set_err(t_mshl *m, int ret, int opt, ...)
{
	va_list ap;

	va_start(ap, opt);
	ft_bzero(m->err_to_print, PATH_MAX + 1);
	ft_strcpy(m->err_to_print, "minishell: ");
	if (opt >= 1)
	{
		ft_strcat(m->err_to_print, va_arg(ap, char*));
		ft_strcat(m->err_to_print, ": ");
	}
	if (opt == 3)
		ft_strcat(m->err_to_print, "`");
	if (opt >= 2)
	{
		ft_strcat(m->err_to_print, va_arg(ap, char*));
		if (opt == 3)
			ft_strcat(m->err_to_print, "'");
		ft_strcat(m->err_to_print, ": ");
	}
	ft_strcat(m->err_to_print, va_arg(ap, char*));
	m->err = ret;
	reat_crval(m, ret);
	va_end(ap);
	return (ret);
}
