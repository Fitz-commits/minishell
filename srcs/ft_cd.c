# include "minishell.h"
/*
int		count_lws(char* )
{
	int i;


}
char *rince_slashes(char *path)
{

}*/

int set_oldpwd(t_mshl *m, int i, int j)
{
	char *tempc;
	if (i != -1 && j != -1)
    	{
	    	free(m->cenv[i]);
	   		if (!(m->cenv[i] = pair_value_key(getvar(m, "PWD"), "OLDPWD")))
		    return (EXIT_FAILURE);
    	}
    	else if (i == -1 && j != -1)
    	{
      	  if (!(tempc = pair_value_key(getvar(m, "PWD"), "OLDPWD")))
          	  return (EXIT_FAILURE);
     	   if (!(m->cenv = ft_append(m, tempc)))
        	   return (EXIT_FAILURE);
   		}
	return (EXIT_SUCCESS);
}

int		set_pwd(t_mshl *m, char buffer[1024], int j)
{
	char *tempc;

	if (j != -1)
    {
	    free(m->cenv[j]);
	    if (!(m->cenv[j] = pair_value_key(buffer, "PWD")))
		    return (EXIT_FAILURE);
    }
    else
    {
        if (!(tempc = pair_value_key(buffer , "PWD")))
            return (EXIT_FAILURE);
        if (!(m->cenv = ft_append(m, tempc)))
            return (EXIT_FAILURE);
    }
	return (EXIT_SUCCESS);
}
int			set_del_pwd(t_mshl *m, int i, int j)
{
	if (j == -1)
	{
		if (i != -1)
			if(del_varenv(m, i))
				return (EXIT_FAILURE);
	}
	else 
	{
		if ((set_oldpwd(m,i,j)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
int			change_pwd(t_mshl *m)
{
	int		i;
	int		j;
	char	buffer[PATH_MAX];

	i = find_env(m->cenv, "OLDPWD=");
	j = find_env(m->cenv, "PWD=");
    ft_bzero(buffer, PATH_MAX);
    if (!(getcwd(buffer, PATH_MAX)))
	{
		errno = 0;
		if (set_oldpwd(m, i, j))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (set_del_pwd(m, i, j))
		return (EXIT_FAILURE);
    if (set_pwd(m, buffer, j))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			go_home(t_mshl *m)
{
    if (find_env(m->cenv, "HOME") != -1)
    {
        chdir(getvar(m, "HOME"));
        if (errno)
            return (EXIT_FAILURE);
        change_pwd(m);
        return (EXIT_SUCCESS);
    }
    ft_putstr_fd("minishell: cd: HOME not set\n", m->tstdout);
    return (EXIT_FAILURE);
}

//might want to return other value for error
int			ft_cd(t_mshl *m)
{	
    if (!m->cpargs[1])
        return(go_home(m));
    if (!m->cpargs[1][0])
    {
        chdir(".");
        return (change_pwd(m));
    }
    if (check_dperm(m, m->cpargs[1]))
        return (EXIT_FAILURE);
    if ((chdir(m->cpargs[1])) == -1)
        return (EXIT_FAILURE);
	return (change_pwd(m)); //protect malloc
}

