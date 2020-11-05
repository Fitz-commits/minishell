#include "minishell.h"

int		set_bpwd(t_mshl *m)
{
	char		buffer[PATH_MAX];
	char		*tempc;

	if (!(getcwd(buffer, PATH_MAX)))
		return (EXIT_SUCCESS);
	if (!(tempc = pair_value_key(buffer, "PWD")))
		return (set_err(m, 1, 0, strerror(ENOMEM)));
	if (!(m->cenv = ft_append(m, tempc)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		complete_env(t_mshl *m)
{
	int		i;

	i = find_env(m->cenv, "PWD");
	if (i == -1)
		if (!(set_bpwd(m)))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		env(t_mshl *m)
{
	int		i;

	i = 0;
	while (m->cenv[i])
		ft_putendl_fd(m->cenv[i++], m->tstdout);
	close_rp(m);
	return (1);	
}
