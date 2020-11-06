/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:07:58 by chris             #+#    #+#             */
/*   Updated: 2020/11/06 21:12:22 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*catch_key(char *str, int *to_erase)
{
	int			l;
	char		*ret;

	l = 0;
	*to_erase = 1;
	while(str[*to_erase])
	{
		if (str[*to_erase] == '{'|| str[*to_erase] == '}')
			l += 1;
		if (str[*to_erase] && str[*to_erase] != '$' &&
				(ft_isalnum(str[*to_erase]) || str[*to_erase] ==
				 '{'||str[*to_erase] == '}'|| str[*to_erase] == '?'||
				 str[*to_erase] == '_'))
			*to_erase += 1;
		else
			break;
		if (str[*to_erase] == '}' || str[*to_erase] == '?' ||
				(ft_isdigit(str[*to_erase]) && *to_erase == 1))
			break;
	}
	if (l == 2)
		l = 1;
	if (!(ret = ft_strndup(&str[l + 1], *to_erase - l - 1)))
		return (NULL);
	return (ret);
}

int			assemble_string(t_mshl *m, char *buffer, int to_erase)
{
	char		*ret;
	int			total_len;
	int			i;

	i = -1;
	total_len = ft_strlen(m->reader) + ft_strlen(getvar(m, buffer)) - to_erase;
	if (!(ret = malloc(sizeof(char) * (total_len + 2))))
		return (set_err(m, 1, 0, strerror(ENOMEM)));
	while (++i < m->pos)
		ret[i] = m->reader[i];

	ft_strcpy(&ret[i], getvar(m,buffer));
	i += ft_strlen(getvar(m, buffer));
	while(i < total_len &&  m->reader[m->pos + to_erase])
	{
		ret[i++] = m->reader[m->pos + to_erase++];
	}
	ret[i] = 0;
	free(m->reader);
	m->reader = ret;
	return (EXIT_SUCCESS);
}

int			env_expension(t_mshl *m)
{
	int		i;
	int		flag;
	int		to_erase;
	char	*buffer;

	flag = 0;
	i = 0;
	while(m->reader)
	{	
		m->pos = 0;
		if ((m->reader[i] == '$' && (flag == 0 || flag == 2)))
		{
			if(!(buffer = catch_key(&m->reader[i], &to_erase)))
				return (set_err(m, 1, 0, strerror(ENOMEM)));
			m->pos = i;
			if (assemble_string(m, buffer, to_erase))
				return (free_str(&buffer, EXIT_FAILURE));
			i += ft_strlen(getvar(m, buffer));
			free(buffer);
		}
		else
			i++;
		if (!m->reader[i])
			break;
		flag = set_quotes(flag, m->reader[i]);
	}
	return (EXIT_SUCCESS);
}

int			check_lee(char *line)
{
	int		flag;
	int		i;

	i = -1;
	flag = 0;
	while (line[++i])
	{
		if ((line[i] == '$' && (flag == 0 || flag == 2)))
			return (1);
		flag = set_quotes(flag, line[i]);
	}
	return (0);
}

int check_for_exp(t_mshl *m)
{
	if (check_lee(m->reader))
		if ((env_expension(m)))
			return (set_err(m, 1, 0, strerror(ENOMEM)));
	return (EXIT_SUCCESS);
}
