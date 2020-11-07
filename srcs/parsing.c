/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:33:39 by chris             #+#    #+#             */
/*   Updated: 2020/11/07 12:02:21 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** flag == 1 -> '
** flag == 2 -> "
** flag == 0 -> unquoted
** flag == 3 -> after slash
** flag == 5 after slash in quotes
*/

int			set_quotes(int flag, char c)
{
	if (flag == 2 && c == '\\')
		return (5);
	if (flag == 5)
		return (2);
	if (flag == 0 && c == '"')
		return (2);
	if (flag == 0 && c == '\'')
		return (1);
	if (flag == 1 && c == '\'')
		return (0);
	if (flag == 2 && c == '"')
		return (0);
	if (flag == 0 && c == '\\')
		return (3);
	if (flag == 3)
		return (0);
	return (flag);
}

int			count_arg(char *line, int i, int j)
{
	int flag;
	int k;

	flag = 0;
	i = 0;
	j = 0;
	k = 0;
	while (line[i])
	{
		k = 0;
		while (is_space(line[i]))
			i++;
		if (is_delim(line[i]))
		{
			j++;
			i++;
		}
		while (line[k + i] && !(!(flag) && is_delim(line[k + i])))
			flag = set_quotes(flag, line[k++ + i]);
		if (k != 0)
			j++;
		i += k;
	}
	return (j);
}

/*
**	need to differiencate between a delimiter and a space because the
** intaraction are not the same
**	we need to split on an unquoted unescaped space and not keep it
**	and we need to split on an unquoted unescaped delimiter and keep
** it in a separate tab entry
**	| use the output of a commant as stdin of another command
**	> redirect the standard output of a command
**	< redirect the standard input of a command
*/

char		*alloc_sep(char c, int *i)
{
	char *ret;

	if (!(ret = malloc(sizeof(char) * 2)))
		return (NULL);
	ret[0] = c;
	ret[1] = 0;
	(*i) += 1;
	return (ret);
}

int			triming(char **line, char ***ret, int *flag, int *j)
{
	int		k;
	char	*nline;
	char	**nret;
	int		i;

	i = 0;
	nret = *ret;
	nline = *line;
	while (nline[i])
	{
		k = 0;
		while (is_space(nline[i]))
			i += 1;
		if (is_delim(nline[i]))
			if (!(nret[(*j)++] = alloc_sep(nline[i], &i)))
				return (EXIT_FAILURE);
		while (nline[k + i] && !(!(*flag) && is_delim(nline[k + i])))
			*flag = set_quotes(*flag, nline[k++ + i]);
		if (k != 0)
			if (!(nret[(*j)++] = ft_strndup(&nline[i], k)))
				return (EXIT_FAILURE);
		i += k;
	}
	return (EXIT_SUCCESS);
}

char		**parse_cli(char *line, t_mshl *m)
{
	int		j;
	int		flag;
	char	**ret;

	if (!(ret = malloc(sizeof(char*) * (count_arg(line, 0, 0) + 1))))
	{
		set_err(m, 1, 0, strerror(ENOMEM));
		return (NULL);
	}
	flag = 0;
	j = 0;
	if ((triming(&line, &ret, &flag, &j) == EXIT_FAILURE))
	{
		set_err(m, 1, 0, strerror(ENOMEM));
		free_tab(ret, 0, 1);
		return (NULL);
	}
	ret[j] = 0;
	if (flag != 0)
	{
		set_err(m, 2, 0, "unexpected end of file");
		return (free_tabs(ret));
	}
	return (ret);
}
