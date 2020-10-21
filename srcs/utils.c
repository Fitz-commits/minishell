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
	char	**ret;
	int		i;

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

void itaob(int a, char **buff)
{
    int j;
    char *buf;

    buf = *buff;
    j = size(a); 
    buf[j] = 0;
    j -= 1;
    while(j >= 0)
    {
        buf[j--] = (a % 10) + 48;
        a = a / 10;
    }
}

int		reat_crval(t_mshl *m, int i)
{
	m->rvalue = i;
	itaob(i, &m->crvalue);
	return (0);
}

int		find_equ(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	**tabdup(char **tab)
{
	int		i;
	int		len;
	char	**newtab;

	i = 0;
	len = tablen(tab);
	if (!(newtab = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (i <= len)
		newtab[i++] = NULL;
	i = 0;
	while (i < len)
	{
		if(!(newtab[i] = strdup(tab[i])))
		{
			free_tab(newtab, 0, 1);
			return (NULL);
		}
		i++;
	}
	return (newtab);
}

void	sort_tab(char **tab)
{
	int i;
	int len;
	int loop;
	char *tmp;

	loop = 1;
	len = tablen(tab);
	while (loop)
	{
		loop = 0;
		i = 0;
		while (i < len - 1)
		{
			if (ft_strncmp(tab[i], tab[i + 1], find_equ(tab[i])) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				loop = 1; 
			}
			i++;
		} 
	}
}