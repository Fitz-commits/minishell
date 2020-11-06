/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:25:44 by chris             #+#    #+#             */
/*   Updated: 2020/11/06 22:34:26 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_for_pdq(t_mshl *m, char *str)
{
    char ret[2];
	int i;

	i = 0;
	if (str[0] == '|' || str[0] == ';')
	{
		ret[0] = str[0];
        ret[1] = 0;
        return (set_err(m, 2, 1, "parsing error near", ret));
	}
	while (str[i] && is_space(str[i]))
	{
		i++;
		if (str[i] && (str[i] == ';' || str[i] == '|'))
		{
			ret[0] = str[i];
            ret[1] = 0;
            return (set_err(m, 2, 1, "parsing error near", ret));
		}
	}
	return (EXIT_SUCCESS);
}

int		first_parsing(t_mshl *m, char *str)
{
	int		i;
	int		q;
	int		err;

	i = 0;
	q = 0;
	if (check_for_pdq(m, str))
		return (2);
	while (str[i])
	{
		if (!q)
		{
			err = check_pni_errors(m, str, i);
			if (err != 0)
				return (2);
		}
		q = set_quotes(q, str[i]);
		i++;
	}
	return (0);
}

int			is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f')
		return 1;
	return 0;
}

int			is_delim(char c)
{
	if (c == ';' || c == '>' || c == '<' || c == '|' || is_space(c))
		return (1);
	return (0);
}
