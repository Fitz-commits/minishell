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
*/
int	ft_exec(t_mshl *m, char *path)
{
	// need to close unused end
	errno = 0;
	if (m->tstdout == -1)
		return (m->tstdout = 1);
	if (m->tstdout == -1)
		return (m->tstdout = 0);
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
		execve(path, m->cpargs, m->cenv);
	}
	close_rp(m);
	m->proc.curpro++;
	free(path);
	return (0);
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
	if (ft_strchr(m->cpargs[0], '/'))
	{
		stat(m->cpargs[0], &buffer);
		if (S_ISREG(buffer.st_mode))
			return (ft_exec(m, m->cpargs[0]));
	}
	if (!(pathtab = ft_split(path, ':')))
		return (m->err = 3); // Memory error
	while (pathtab[i])
	{
		temp = path_join(pathtab[i], m->cpargs[0]);
		stat(temp, &buffer);
		if (S_ISREG(buffer.st_mode))
			return (ft_exec(m, temp));
		free(temp);
		i++;
	}
	errno = 0;
	return (m->err = 127); // not command not found 127
}
