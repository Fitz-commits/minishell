/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 00:49:09 by marvin            #+#    #+#             */
/*   Updated: 2020/11/07 12:20:10 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		handler(int sign)
{
	signal(sign, handler);
	ft_putstr_fd("\n", 1);
	display_prompt();
}

void		var_handler(int sign)
{
	signal(sign, handler);
	ft_putstr_fd("\n", 1);
}
