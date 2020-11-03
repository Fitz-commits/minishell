//need to check for leaks and error returns

#include "minishell.h"
/*
**cette fonction rassemble l'argument entré dans le shell avec un repertoire
**path pour pouvoir lancer un programme
**
*/
char	*path_join(char *path, char *arg)
{
	int len;
	int i;
	int j;
	char *ret;

	len = ft_strlen(path) + ft_strlen(arg) + 2;
	if (!(ret = malloc(sizeof(char) * len)))
		return NULL;
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
/*
**lance un sous process avec fork et exec la commande donnée en args[0]
**
** might want to add after errno = 0 mechanism for std -1
*/
int	ft_exec(t_mshl *m, char *path)
{
	// need to close unused end
	errno = 0;

	m->proc.child_pid[m->proc.curpro] = fork();
	if (m->proc.child_pid[m->proc.curpro] == 0)
	{	
		if (m->cp >= 0 && m->tstdout == m->tpiped[m->cp][1] && m->tpiped[m->cp][0])
			close(m->tpiped[m->cp][0]);
		if (m->cp >= 0 && m->tstdin && m->tstdin == m->tpiped[m->cp][0] && m->tpiped[m->cp][1])
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
int change_margs(t_mshl *m, char *path)
{
	int i;

	i = -1;

	while (m->args[++i])
		if (m->args[i] == m->cpargs[0])
			{
				free(m->args[i]);
				m->args[i] = path;
				m->cpargs[0] = path;
			}
	return (EXIT_SUCCESS);
}
/*
**
**regarde d'abord sur c'est un path relative check avec stat si le fichier existe
**puis l'execute
**puis cherche dans tout les path si un ficher avec le nom existe et l'execute
*/
int	launch_exec(t_mshl *m, char *path)
{
	int i;
	char **pathtab;
	char *temp;
	struct stat buffer;

	i = 0;
	if (ft_strchr(m->cpargs[0], '/') || !getvar(m, "PATH")[0])
	{
		if (!check_fperm(m, m->cpargs[0], NULL))
			return (ft_exec(m, m->cpargs[0]));
		else
			return(EXIT_FAILURE);
	}
	if (!(pathtab = ft_split(path, ':')))
		return (m->err = 3); // Memory error
	while (pathtab[i])
	{
		if (!(temp = path_join(pathtab[i], m->cpargs[0])))
			return (EXIT_FAILURE);
		stat(temp, &buffer);
		if (S_ISREG(buffer.st_mode))
        {	
			free_tab(pathtab, 1, 1);
			change_margs(m, temp);
			if (!(check_fperm(m, m->cpargs[0], &buffer)))
				return (ft_exec(m, m->cpargs[0]));
			else
				return(EXIT_FAILURE);
        }
		free(temp);
		i++;
	}
    free_tab(pathtab, 1, 1);
	errno = 0;
	return (m->err = 127); // not command not found 127
}
