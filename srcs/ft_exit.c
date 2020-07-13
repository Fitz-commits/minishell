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
	ft_putendl_fd("-- Free struct --", m->tstdout);
	ft_putendl_fd("free args", 1);
	free_tab(m->args, 1, 1);
	ft_putendl_fd("free cpargs", 1);
	free_tab(m->cpargs, 1, 1);
	ft_putendl_fd("free cenv", 1);
	free_tab(m->cenv, 1, 1);
	ft_putendl_fd("free prompt", 1);
	//free_str(&m->prompt, 1);
	//ft_putendl_fd("free struct pointer", 1);
	//free(m);
	return (ret);
}