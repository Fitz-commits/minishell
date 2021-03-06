/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:49:14 by marvin            #+#    #+#             */
/*   Updated: 2020/11/07 11:06:13 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_nbr(char *str, int sign)
{
	int			i;
	int			len;
	long long	nb;

	i = 0;
	len = 0;
	nb = 0;
	while (str[i] == '0')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		if ((len += 1) > 19)
			return (1);
		nb = nb * 10 + str[i] - '0';
		if ((long)nb < 0 && ((nb * -1) != LLONG_MIN || sign == 1))
			return (1);
		i++;
	}
	return (0);
}

int			parse_exit_code(char *str)
{
	int					i;
	int					sign;

	i = 0;
	sign = 1;
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
				|| str[i] == '\v' || str[i] == '\f' || str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (!str[i])
		return (1);
	if (check_nbr(&str[i], sign))
		return (1);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && (str[i] == '\t' || str[i] == ' '))
		i++;
	if (str[i])
		return (1);
	return (0);
}

int			ft_exit(t_mshl *m, int error)
{
	if (m->nb_cpargs > 1)
	{
		if (parse_exit_code(m->cpargs[1]))
		{
			set_err(m, 255, 2, "exit", m->cpargs[1],
					"numeric argument required");
			ft_putendl_fd(m->err_to_print, 2);
		}
		else if (m->nb_cpargs > 2)
		{
			set_err(m, 1, 1, "exit", "too many arguments");
			ft_putendl_fd(m->err_to_print, 2);
		}
		else
			m->rvalue = ft_atoi(m->cpargs[1]);
	}
	free_all(m);
	if (error)
		exit(error);
	exit(m->rvalue);
	return (m->rvalue);
}
