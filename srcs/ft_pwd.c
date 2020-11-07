/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:36:31 by chris             #+#    #+#             */
/*   Updated: 2020/11/06 22:36:32 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(t_mshl *m)
{
	char buff[PATH_MAX];

	getcwd(buff, PATH_MAX);
	ft_putstr_fd(buff, m->tstdout);
	ft_putstr_fd("\n", m->tstdout);
	close_rp(m);
	return (0);
}
