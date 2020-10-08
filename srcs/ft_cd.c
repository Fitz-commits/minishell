# include "minishell.h"


int	change_pwd(t_mshl *m)
{
	int i;
	int j;
	char buffer[PATH_MAX];

	i = find_env(m->cenv, "OLDPWD=");
	j = find_env(m->cenv, "PWD=");
	free(m->cenv[i]);
	if (!(m->cenv[i] = pair_value_key(getvar(m, "PWD"), "OLDPWD")))
		return (1);
	free(m->cenv[j]);
	getcwd(buffer, PATH_MAX);
	if (!(m->cenv[j] = pair_value_key(buffer, "PWD")))
		return (1);
	return (0);
}

int go_home(t_mshl *m)
{
    if (find_env(m->cenv, "HOME") != -1)
    {
        chdir(getvar(m, "HOME"));
        if (errno)
            return (1);
        change_pwd(m);
        return (0);
    }
    else
        return (1);
}

//might want to return other value for error
int	ft_cd(t_mshl *m)
{
	struct stat buffer;
	
    if (!m->cpargs[1])
        return(go_home(m));
	stat(m->cpargs[1], &buffer);
	if (errno)
		return (1);
	if (S_ISDIR(buffer.st_mode))
	{
		chdir(m->args[1]);
		if (errno)
			return (1);
		else
			return (change_pwd(m)); //protect malloc
	}
	else if (S_ISREG(buffer.st_mode))
	{	
		ft_putstr_fd(m->cpargs[1], m->tstdout);
		ft_putendl_fd(" is a file not a directory", m->tstdout);
	}
	else 
	{
		return (errno);
	}
	return (1);
}

