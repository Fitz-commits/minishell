#include "minishell.h"

int	env(t_mshl *m)
{
	int i;
	i = 0;
	while (m->cenv[i])
		ft_putendl_fd(m->cenv[i++], 1);
	return (1);	
}