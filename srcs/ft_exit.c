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

int			only_z(char *str)
{
	int					i;
	int					sign;
	long long			nb;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' '))
		i++;
	if (str[i] == '+' || (str[i] == '-' && (sign = -1)))
		i++;
	if (!str[i])
		return (1);
	while (str[i] && ft_isdigit(str[i]))
	{
		nb = nb * 10 + str[i] - '0';
		if ((long)nb < 0)
			return (1);
		i++;
	}
	
	while (str[i] && (str[i] == '\t' || str[i] == ' '))
		i++;
	if (str[i])
		return (1);
	
	return (0);
}

int			free_all(t_mshl *m)
{
	free(m->crvalue);
	if (m->args)
        free_tab(m->args, 1, 1);
	if (m->cpargs) 
        free(m->cpargs);
	free_tab(m->cenv, 1, 1);
	return (0);
}

int			ft_exit(t_mshl *m, int error)
{
	int ret;

	ret = 0;
	/*if (m->nb_cpargs > 2)
	{
		m->err = 11;
		ft_error(m);
		ret = 1;
	}*/
	if (m->nb_cpargs > 1)
	{
		if (/*!(ret = ft_atoi(m->cpargs[1])) && */only_z(m->cpargs[1]))
		{
			m->err = 255;
			m->errarg = 1;
			ft_error(m);
			ret = 255;
			//return (ft_error(m));
		}
		else if (m->nb_cpargs > 2)
		{
			m->err = 11;
			ft_error(m);
			ret = 1;
		}
		else
			ret = ft_atoi(m->cpargs[1]);
	}
	/*if (m->cpargs[1])
		ret = ft_atoi(m->cpargs[1]);*/
    free_all(m);
	//free_str(&m->prompt, 1);
	//ft_putendl_fd("free struct pointer", 1);
	//free(m);
	if (error)
		exit(error);
    exit(ret);
	return (ret);
}

