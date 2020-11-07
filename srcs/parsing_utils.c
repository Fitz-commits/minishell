/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:50:46 by chris             #+#    #+#             */
/*   Updated: 2020/11/07 11:53:20 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_chev_o(t_mshl *m, char *str, int i)
{
	char ret[2];

	if (!ft_strncmp(&str[i], "<|", 2) || !ft_strncmp(&str[i], "<>", 2)
			|| !ft_strncmp(&str[i], "< <", 3) || !ft_strncmp(&str[i], "< ;", 3))
	{
		ret[0] = str[i];
		ret[1] = 0;
		return (set_err(m, 2, 1, "parsing error near", ret));
	}
	if (!ft_strncmp(&str[i], "<<", 2))
	{
		ret[0] = str[i];
		ret[1] = 0;
		return (set_err(m, 2, 1, "not implemented near", ret));
	}
	return (0);
}

int		check_pipe(t_mshl *m, char *str, int i)
{
	char ret[2];

	if (!ft_strncmp(&str[i], "|>", 2) || !ft_strncmp(&str[i], "|<", 2)
			|| !ft_strncmp(&str[i], "| ;", 3) || !ft_strncmp(&str[i], "|;", 2))
	{
		ret[0] = str[i];
		ret[1] = 0;
		return (set_err(m, 2, 1, "parsing error near", ret));
	}
	if (!ft_strncmp(&str[i], "||", 2))
	{
		ret[0] = str[i];
		ret[1] = 0;
		return (set_err(m, 2, 1, "not implemented near", ret));
	}
	return (0);
}

int		check_dq(t_mshl *m, char *str, int i)
{
	char ret[2];

	if (!ft_strncmp(&str[i], "; ;", 3) || !ft_strncmp(&str[i], ";;", 2))
	{
		ret[0] = str[i];
		ret[1] = 0;
		return (set_err(m, 2, 1, "parsing error near", ret));
	}
	return (0);
}

int		check_chev_f(t_mshl *m, char *str, int i)
{
	char ret[2];

	if (!ft_strncmp(&str[i], ">|", 2) || !ft_strncmp(&str[i], "><", 2) ||
			!ft_strncmp(&str[i], ">>>", 3) || !ft_strncmp(&str[i], "> >", 3) ||
			!ft_strncmp(&str[i], "> ;", 3))
	{
		ret[0] = str[i];
		ret[1] = 0;
		return (set_err(m, 2, 1, "parsing error near", ret));
	}
	return (0);
}

int		check_pni_errors(t_mshl *m, char *str, int i)
{
	char ret[2];

	if (str[i] == ';')
		return (check_dq(m, str, i));
	if (str[i] == '<')
		return (check_chev_o(m, str, i));
	if (str[i] == '>')
		return (check_chev_f(m, str, i));
	if (str[i] == '|')
		return (check_pipe(m, str, i));
	if (str[i] == '*' || !ft_strncmp(&str[i], "&&", 2) || str[i] == '&')
	{
		ret[0] = str[i];
		ret[1] = 0;
		return (set_err(m, 2, 1, "not implemented near", ret));
	}
	return (0);
}
