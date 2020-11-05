/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 23:17:45 by marvin            #+#    #+#             */
/*   Updated: 2020/11/05 23:18:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	until_dquotes(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if (line[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/*
** return the line corresponding to the $variable
*/

int	find_env(char **env, char *key)
{
	int i;
	int dq;
	int j;
	char buffer[512];

	i = 0;
	ft_bzero(buffer, 512);
	while(env[i])
	{	
		j = -1;
		dq = until_dquotes(env[i]);
		while(++j < dq)
			buffer[j] = env[i][j];
		buffer[j] = 0;
		if (!ft_strcmp(key, buffer))
			return (i);
		i++;
	}
	return (-1);
}

int		set_bpwd(t_mshl *m)
{
	char		buffer[PATH_MAX];
	char		*tempc;

	if (!(getcwd(buffer, PATH_MAX)))
		return (EXIT_SUCCESS);
	if (!(tempc = pair_value_key(buffer, "PWD")))
		return (set_err(m, 1, 0, strerror(ENOMEM)));
	if (!(m->cenv = ft_append(m, tempc)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		complete_env(t_mshl *m)
{
	int		i;

	i = find_env(m->cenv, "PWD");
	if (i == -1)
		if (!(set_bpwd(m)))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		env(t_mshl *m)
{
	int		i;

	i = 0;
	while (m->cenv[i])
		ft_putendl_fd(m->cenv[i++], m->tstdout);
	close_rp(m);
	return (1);	
}
