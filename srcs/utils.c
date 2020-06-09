/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 17:09:50 by marvin            #+#    #+#             */
/*   Updated: 2020/03/26 17:09:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tablen(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

char **cpy_args(char **args, int beg, int end)
{
	char **ret;
	int i;

	i = 0;
	if (!(ret = malloc (sizeof(char *) * (end - beg + 1))))
		return (NULL);
	while (beg < end && (args[beg]))
	{
		ret[i++] = args[beg++];
	}
	ret[i] = NULL;
	return (ret);
}

int clear_std(t_mshl *m)
{
	/*if (m->piped[1] != 1)
		close(m->piped[1]);
	m->piped[1] = 1;
	if (m->piped[0] != 0)
		close(m->piped[0]);
	m->piped[0] = 0;
	*/
	if (m->tstdout != 1)
		if (close(m->tstdout) == -1)
			return (1);
	m->tstdout = 1;
	if (m->tstdin)
		if ((close(m->tstdin) == -1))
			return (1);
	m->tstdin = 0;
	return (0);
}

void print_tab(char **tab)
{
	int i;
	i = 0;
	while (tab[i])
		ft_putendl_fd(tab[i++], 1);
}

void	display_prompt(t_mshl *m)
{
	write(m->tstdout, m->prompt, ft_ilen(m->prompt));
}