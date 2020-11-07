/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:41:19 by chris             #+#    #+#             */
/*   Updated: 2020/11/07 19:13:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*path_join(char *path, char *arg)
{
	int		len;
	int		i;
	int		j;
	char	*ret;

	len = ft_strlen(path) + ft_strlen(arg) + 2;
	if (!(ret = malloc(sizeof(char) * len)))
		return (NULL);
	i = 0;
	while (path[i])
	{
		ret[i] = path[i];
		i++;
	}
	ret[i++] = '/';
	j = 0;
	while (arg[j])
		ret[i++] = arg[j++];
	ret[i] = 0;
	return (ret);
}

int			ft_exec(t_mshl *m, char *path)
{
	errno = 0;
	m->proc.child_pid[m->proc.curpro] = fork();
	if (m->proc.child_pid[m->proc.curpro] == 0)
	{
		if (m->cp >= 0 && m->tstdout ==
				m->tpiped[m->cp][1] && m->tpiped[m->cp][0])
			close(m->tpiped[m->cp][0]);
		if (m->cp >= 0 && m->tstdin && m->tstdin ==
				m->tpiped[m->cp][0] && m->tpiped[m->cp][1])
			close(m->tpiped[m->cp][1]);
		if (m->tstdin != 0)
			dup2(m->tstdin, STDIN_FILENO);
		if (m->tstdout != 1)
			dup2(m->tstdout, STDOUT_FILENO);
		if ((execve(path, m->cpargs, m->cenv)))
			exit(0);
	}
	close_rp(m);
	m->proc.curpro++;
	return (0);
}

int			change_margs(t_mshl *m, char **path)
{
	int i;

	i = -1;
	while (m->args[++i])
	{
		if (!ft_strcmp(m->args[i], m->cpargs[0]))
		{
			free(m->args[i]);
			m->args[i] = *path;
			m->cpargs[0] = *path;
			return (EXIT_SUCCESS);
		}
	}
	free(*path);
	return (EXIT_FAILURE);
}

int			search_exec(t_mshl *m, char ***pathtab)
{
	int				i;
	char			*tempc;
	char			**path;
	struct stat		buffer;

	i = 0;
	path = *pathtab;
	while (path[i])
	{
		if (!(tempc = path_join(path[i], m->cpargs[0])))
			return (set_err(m, 1, 0, strerror(ENOMEM)));
		stat(tempc, &buffer);
		if (S_ISREG(buffer.st_mode))
		{
			free_tab(path, 1, 1);
			change_margs(m, &tempc);
			if (!(check_fperm(m, m->cpargs[0], &buffer)))
				return (ft_exec(m, m->cpargs[0]));
			return (EXIT_FAILURE);
		}
		free(tempc);
		i++;
	}
	free_tab(path, 1, 1);
	return (set_err(m, 127, 1, m->cpargs[0], "command not found"));
}

int			launch_exec(t_mshl *m, char *path)
{
	char		**pathtab;

	signal(SIGINT, var_handler);
	signal(SIGQUIT, var_handler);
	if (ft_strchr(m->cpargs[0], '/') || !getvar(m, "PATH")[0])
	{
		if (!check_fperm(m, m->cpargs[0], NULL))
			return (ft_exec(m, m->cpargs[0]));
		else
			return (EXIT_FAILURE);
	}
	if (!(pathtab = ft_split(path, ':')))
		return (set_err(m, 1, 0, strerror(ENOMEM)));
	return (search_exec(m, &pathtab));
}
