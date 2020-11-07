/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 23:19:55 by marvin            #+#    #+#             */
/*   Updated: 2020/11/07 11:32:28 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Most of the C compilers support a third parameter to main which
** store all envorinment variables
** int main(int argc, char *argv[], char * envp[])
** makes a copy of env to work with
*/

int		print_warning(t_mshl *m, int nb)
{
	char *strnb;

	ft_putstr_fd("minishell: warning: shell level (", m->tstdout);
	if (!(strnb = ft_itoa(nb)))
		return (set_err(m, 1, 0, strerror(ENOMEM)));
	ft_putstr_fd(strnb, m->tstdout);
	free_str(&strnb, 0);
	ft_putstr_fd(") too high, resetting to 1\n", m->tstdout);
	return (0);
}

int		add_var(t_mshl *m)
{
	int		len;
	int		i;
	char	**new;

	len = tablen(m->cenv);
	if (!(new = (char **)malloc(sizeof(char *) * (len + 2))))
		return (EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		if (!(new[i] = ft_strdup(m->cenv[i])))
			return (free_tab(new, 3, 1));
		i++;
	}
	if (!(new[i] = ft_strdup("SHLVL=1")))
		return (free_tab(new, 3, 1));
	i++;
	new[i] = NULL;
	free_tab(m->cenv, 0, 1);
	m->cenv = new;
	return (0);
}

char	**ft_getenv(char **env)
{
	int		i;
	char	**ret;

	i = 0;
	while (env[i])
		i++;
	if (!(ret = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (!(ret[i] = ft_strdup(env[i])))
			return (free_tabs(ret));
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int		env_init(t_mshl *m, char **env)
{
	if (!(m->cenv = ft_getenv(env)))
		return (set_err(m, 1, 0, strerror(ENOMEM)));
	if (init_shlvl(m))
		return (set_err(m, 1, 0, strerror(ENOMEM)));
	return (EXIT_SUCCESS);
}
