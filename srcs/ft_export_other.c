/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_other.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 23:12:11 by marvin            #+#    #+#             */
/*   Updated: 2020/11/07 11:08:18 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*pair_value_key(char *value, char *key)
{
	int		i;
	int		j;
	int		size;
	char	*ret;

	i = 0;
	j = 0;
	size = ft_strlen(value) + ft_strlen(key) + 2;
	if (!(ret = malloc(sizeof(char) * size)))
		return (NULL);
	while (key[i])
		ret[j++] = key[i++];
	ret[j++] = '=';
	i = 0;
	while (value[i])
		ret[j++] = value[i++];
	ret[j] = 0;
	return (ret);
}

/*
** get the value associated with "$key" variable
*/

char		*getvar(t_mshl *m, char *key)
{
	int nline;

	signal(SIGINT, var_handler);
	signal(SIGQUIT, var_handler);
	if (key[0] == '?')
		return (m->crvalue);
	if (!key[0])
		return ("$");
	nline = find_env(m->cenv, key);
	if (nline == -1)
		return ("");
	else
		return (&m->cenv[nline][until_dquotes(m->cenv[nline]) + 1]);
}
