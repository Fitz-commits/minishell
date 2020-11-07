/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 17:09:50 by marvin            #+#    #+#             */
/*   Updated: 2020/11/07 12:22:34 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			tablen(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

char		**cpy_args(char **args, int beg, int end)
{
	char	**ret;
	int		i;

	i = 0;
	if (!(ret = malloc(sizeof(char *) * (end - beg + 1))))
		return (NULL);
	while (beg < end && (args[beg]))
	{
		ret[i++] = args[beg++];
	}
	ret[i] = NULL;
	return (ret);
}

int			clear_std(t_mshl *m)
{
	int i;

	i = -1;
	if (m->tstdout > 1)
		if (close(m->tstdout) == -1)
			return (1);
	while (++i <= m->cp)
		if (m->tpiped[i][1] == m->tstdout)
			m->tpiped[i][1] = 0;
	m->tstdout = 1;
	if (m->tstdin)
		if ((close(m->tstdin) == -1))
			return (1);
	i = -1;
	while (++i <= m->cp)
		if (m->tpiped[i][0] == m->tstdin)
			m->tpiped[i][0] = 0;
	m->tstdin = 0;
	return (0);
}

void		print_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		ft_putendl_fd(tab[i++], 1);
}

void		display_prompt(void)
{
	write(1, "minishell$> ", 12);
}
