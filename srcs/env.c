#include "minishell.h"

int set_pwd(t_mshl *m)
{
    char buffer[PATH_MAX];
    char *tempc;

    getcwd(buffer, PATH_MAX);
    if (!(tempc = pair_value_key(buffer , "PWD")))
        return (EXIT_FAILURE);
    if (!(m->cenv = ft_append(m, tempc)))
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int complete_env(t_mshl *m)
{
    int i;

    i = find_env(m->cenv, "PWD");
    if (i == -1)
        if (!(set_pwd(m)))
            return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int	env(t_mshl *m)
{
	int i;
	i = 0;
	while (m->cenv[i])
		ft_putendl_fd(m->cenv[i++], m->tstdout);
    close_rp(m);
	return (1);	
}
