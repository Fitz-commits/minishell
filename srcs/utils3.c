/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:43:22 by marvin            #+#    #+#             */
/*   Updated: 2020/11/05 22:43:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_append(t_mshl *m, char *str)
{
	char	**new_tab;
	int		i;

	i = tablen(m->cenv);
	if (str)
		i += 1;
	if (!(new_tab = malloc((i + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	if (m->cenv)
		while (m->cenv[i])
		{
			new_tab[i] = m->cenv[i];
			i++;
		}
	free(m->cenv);
	if (str)
	{
		new_tab[i] = str;
		i++;
	}	
	new_tab[i] = NULL;
	return (new_tab);
}

int		close_reset(int fd, int nb)
{
	if (close(fd) == -1)
		return (nb);
	return (nb);
}

int		close_rp(t_mshl *m)
{
	if (m->cp >= 0 && m->tstdin && m->tstdin == m->tpiped[m->cp][0])
	{
		close(m->tstdin);
		m->tstdin = 0;
		m->tpiped[m->cp][0] = 0;
	}
	if (m->cp >= 0 && m->tpiped[m->cp][1])
	{
		close(m->tpiped[m->cp][1]);
		if (m->tstdout == m->tpiped[m->cp][1])
			m->tstdout = 0;
		m->tpiped[m->cp][1] = 0;
	}
	return (EXIT_SUCCESS);
}

int n_command(t_mshl *m)
{
	if (!ft_strcmp(m->cpargs[0], "echo"))
		return (0);
	else if (!ft_strcmp(m->cpargs[0], "env"))
		return (1);
	else if (!ft_strcmp(m->cpargs[0], "export"))
		return (4);
	else if (!ft_strcmp(m->cpargs[0], "cd"))
		return (3);
	else if (!ft_strcmp(m->cpargs[0], "unset"))
		return (2);
    else if (!ft_strcmp(m->cpargs[0], "pwd"))
		return (5);
	else
		return (-1);
}

int size(int a)
{
    int i;
    
    i = 1;
    while (a/10)
    {
        a = a/10;
        i++;
    }
    return (i);
}