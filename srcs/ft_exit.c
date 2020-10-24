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

int		ft_exit(t_mshl *m, int error)
{
	int ret;

	ret = 0;
	if (m->cpargs[1])
		ret = ft_atoi(m->cpargs[1]);
    free(m->crvalue);
	if (m->args)
        free_tab(m->args, 1, 1);
	if (m->cpargs) 
        free(m->cpargs);
	free_tab(m->cenv, 1, 1);
	//free_str(&m->prompt, 1);
	//ft_putendl_fd("free struct pointer", 1);
	//free(m);
	if (error)
		exit(error);
    exit(ret);
	return (ret);
}

