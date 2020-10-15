#include "minishell.h"

int		ft_pwd(t_mshl *m)
{
    char buff[PATH_MAX];

    getcwd(buff, PATH_MAX);
	ft_putstr_fd(buff, m->tstdout);
	ft_putstr_fd("\n", m->tstdout);
	close_rp(m);
	return (0);
}