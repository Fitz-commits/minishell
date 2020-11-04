#include "minishell.h" 
  
// Most of the C compilers support a third parameter to main which 
// store all envorinment variables 
//int main(int argc, char *argv[], char * envp[])
// makes a copy of env to work with

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

int		init_shlvl(t_mshl *m)
{
	int		i;
	int		len;
	int		nb;
	char	*nbstr;

	i = 0;
	nbstr = NULL;
	while (m->cenv[i])
	{
		len = 0;
		while (m->cenv[i][len] != '=' && m->cenv[i][len])
			len++;
		if (!ft_strncmp(m->cenv[i], "SHLVL", len))
		{
			len++;
			nb = ft_atoi(&m->cenv[i][len]) + 1;
			if (nb < 0)
				nb = 0;
			else if (nb > 999)
			{
				if (print_warning(m, nb))
					return (3);
				nb = 1;	
			}
			free_str(&m->cenv[i], 0);
			if (!(nbstr = ft_itoa(nb)))
				return (free_str(&nbstr, 3));
			if (!(m->cenv[i] = ft_strjoin("SHLVL=", nbstr)))
				return (free_str(&nbstr, 3));
			return (free_str(&nbstr, 0));
		}
		i++;
	}
	if (add_var(m))
		return (set_err(m, 1, 0, strerror(ENOMEM)));
	return (0);
}

char	**ft_getenv(char **env)
{
	int i;
	char **ret;

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
		return (set_err(m, 1, 0, strerror(ENOMEM))); //memory error
	if (init_shlvl(m))
		return (set_err(m, 1, 0, strerror(ENOMEM)));
	return (0);
	
}