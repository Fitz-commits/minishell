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
	pid_t child_pid;
	
	child_pid = fork();
	if (child_pid == 0)
	{	
		if (m->tstdin != 0)
			dup2(m->tstdin, 0);
		if (m->tstdout != 1)
			dup2(m->tstdout, 1);
		execve(path, m->cpargs, m->cenv);
	}
	else
		wait(&child_pid);
	return (1);
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
			return ft_exec(m, m->cpargs[0]);
	}
	if (!(pathtab = ft_split(path, ':')))
		return 3;
	while (pathtab[i])
	{
		temp = path_join(pathtab[i], m->cpargs[0]);
		stat(temp, &buffer);
		if (S_ISREG(buffer.st_mode))
			return (ft_exec(m, temp));
		free(temp);
		i++;
	}
	return (1);
}
