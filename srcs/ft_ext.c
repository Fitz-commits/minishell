/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ext.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 23:32:11 by marvin            #+#    #+#             */
/*   Updated: 2020/11/08 13:25:46 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_shlvl2(t_mshl *m, int i, int len)
{
	char	*tempc;
	int		nb;
	char	*nbstr;

	nbstr = NULL;
	nb = ft_atoi(&m->cenv[i][len]) + 1;
	if (nb < 0)
		nb = 0;
	else if (nb > 999)
	{
		if (print_warning(m, nb))
			return (3);
		nb = 1;
	}
	if (!(nbstr = ft_itoa(nb)))
		return (EXIT_FAILURE);
	if (!(tempc = ft_strjoin("SHLVL=", nbstr)))
		return (free_str(&nbstr, 3));
	free_str(&m->cenv[i], 0);
	m->cenv[i] = tempc;
	return (free_str(&nbstr, 0));
}

int			init_shlvl(t_mshl *m)
{
	int		i;
	int		len;

	i = 0;
	while (m->cenv[i])
	{
		len = 0;
		while (m->cenv[i][len] != '=' && m->cenv[i][len])
			len++;
		if (!ft_strncmp(m->cenv[i], "SHLVL", len))
		{
			len++;
			return (init_shlvl2(m, i, len));
		}
		i++;
	}
	if (add_var(m))
		return (EXIT_FAILURE);
	return (0);
}

int			go_home(t_mshl *m)
{
	if (find_env(m->cenv, "HOME") != -1)
	{
		chdir(getvar(m, "HOME"));
		if (errno)
			return (set_err(m, 1, 2, "cd", getvar(m, "HOME"), strerror(errno)));
		change_pwd(m);
		return (EXIT_SUCCESS);
	}
	return (set_err(m, 1, 1, "cd", "HOME not set"));
}
