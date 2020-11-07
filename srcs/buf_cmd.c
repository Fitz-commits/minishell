/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:49:37 by marvin            #+#    #+#             */
/*   Updated: 2020/11/07 10:38:21 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			find_dq(char *str)
{
	int		i;
	int		flag;

	flag = 0;
	i = -1;
	if (!(str))
		return (-1);
	while (str[++i])
	{
		if (str[i] == ';' && !flag)
			return (i);
		flag = set_quotes(flag, str[i]);
	}
	return (-1);
}

char		*copy_until_next_dq(char *src)
{
	char	*dest;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (!(dest = malloc(find_dq(src) + 1)))
		return (NULL);
	while (src[i])
	{
		if (src[i] == ';' && !flag)
			break ;
		else
			dest[i] = src[i];
		i++;
		flag = set_quotes(flag, src[i]);
	}
	dest[i] = 0;
	return (dest);
}

int			alloc_bufcmd(t_mshl *m)
{
	int		dq;

	dq = find_dq(m->reader);
	if (!(m->reader[dq + 1]))
	{
		m->reader[dq] = 0;
		return (EXIT_SUCCESS);
	}
	if (!(m->buff_cmd = ft_strdup(&m->reader[dq + 1])))
		return (set_err(m, 1, 0, strerror(ENOMEM)));
	m->reader[dq] = 0;
	return (EXIT_SUCCESS);
}

int			buf_cmd_to_args(t_mshl *m)
{
	int		dq;
	int		i;

	i = 0;
	while (m->buff_cmd[i] && (dq = find_dq(&m->buff_cmd[i])) == 0)
		i++;
	if (dq == -1 || !m->buff_cmd[0])
	{
		free(m->reader);
		m->reader = m->buff_cmd;
		m->buff_cmd = NULL;
		return (EXIT_SUCCESS);
	}
	if (m->reader)
		free(m->reader);
	if (!(m->reader = copy_until_next_dq(m->buff_cmd)))
		return (set_err(m, 1, 0, strerror(ENOMEM)));
	i = -1;
	while (m->buff_cmd[++i + dq + 1])
		m->buff_cmd[i] = m->buff_cmd[i + dq + 1];
	m->buff_cmd[i] = 0;
	return (EXIT_SUCCESS);
}
