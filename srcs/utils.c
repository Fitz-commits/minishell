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

/*
**	To talk :
**	With the struct we can modify the prompt with a command but
**	for the signal I need to print the prompt but my function can only
**	take one INT arg...
*/ 
void	display_prompt(/*t_mshl *m*/ void)
{
	//write(m->tstdout, m->prompt, ft_ilen(m->prompt));
	write(1, "minishell$> ", 12);
}