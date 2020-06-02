/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:49:14 by marvin            #+#    #+#             */
/*   Updated: 2020/03/26 16:49:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit(t_mshl *m, int ret)
{
	ft_putendl_fd("Free struct", m->tstdout);
	free_tab(m->args, 1, 1);
	return (ret);
}