#include "minishell.h"

void	env(t_mshl *m)
{
	int i;
	i = 0;
	while (m->cenv[i])
		ft_putstr_fd(m->cenv[i++], 1);
}
