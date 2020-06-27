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

int close_reset(int fd, int nb)
{
	if (close(fd) == -1)
		return (nb); // fd error reviewing
	return (nb);
}

int close_rp(t_mshl *m)
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
	return (1);
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
	else
		return (-1);
}