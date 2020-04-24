# include "minishell.h"

int	change_pwd(t_mshl *m)
{
	int i;
	int j;
	char buffer[PATH_MAX];

	i = find_env(m->cenv, "OLDPWD=");
	j = find_env(m->cenv, "PWD=");
	free(m->cenv[i]);
	if (!(m->cenv[i] = pair_value_key(getvar(m->cenv, "PWD"), "OLDPWD")))
		return 22;
	free(m->cenv[j]);
	getcwd(buffer, PATH_MAX);
	if (!(m->cenv[j] = pair_value_key(buffer, "PWD")))
		return 22;
	return (1);
}
//might want to return other value for error
int	ft_cd(t_mshl *m)
{
	struct stat buffer;
	
	stat(m->args[1], &buffer);
	if (S_ISDIR(buffer.st_mode))
	{
		chdir(m->args[1]);
		if (errno == EACCES)
			return (1);
		else
			return (change_pwd(m)); //protect malloc
	}
	else if (S_ISREG(buffer.st_mode))
	{	
		ft_putstr_fd(m->args[1], 1);
		ft_putendl_fd(" is a file not a directory", 1);
	}
	else 
	{
		return (errno);
	}
	return (1);
}

