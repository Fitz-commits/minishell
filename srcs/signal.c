/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 00:49:09 by marvin            #+#    #+#             */
/*   Updated: 2020/11/07 19:38:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_ret;

void		handler(int sign)
{
	if (sign == SIGINT)
		g_ret = 130;
	else if (sign == SIGQUIT)
	{
		g_ret = 131;
		ft_putstr_fd("Quit: ", 1);
		ft_putnbr_fd(sign, 1);
	}
	ft_putstr_fd("\n", 1);
	display_prompt();
	signal(sign, handler);
}

void		var_handler(int sign)
{
	if (sign == SIGINT)
		g_ret = 130;
	else if (sign == SIGQUIT)
	{
		g_ret = 131;
		ft_putstr_fd("Quit:", 1);
		ft_putnbr_fd(sign, 1);
	}
	ft_putstr_fd("\n", 1);
	signal(sign, handler);
}

void	start_sig(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}