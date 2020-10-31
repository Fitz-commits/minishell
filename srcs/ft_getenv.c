#include "minishell.h" 
  
// Most of the C compilers support a third parameter to main which 
// store all envorinment variables 
//int main(int argc, char *argv[], char * envp[])
// makes a copy of env to work with

int		init_shlvl(t_mshl *m)
{
	int i;
	int len;
	int nb;

	i = 0;
	while (m->cenv[i])
	{
		len = 0;
		while (m->cenv[i][len] != '=' && m->cenv[i][len])
			len++;
		if (!ft_strncmp(m->cenv[i], "SHLVL", len))
		{
			len++;
			nb = ft_atoi(&m->cenv[i][len]) + 1;
			free_str(&m->cenv[i], 0);
			if (!(m->cenv[i] = ft_strjoin("SHLVL=", ft_itoa(nb))))
				return (3);
			break;
		}
		i++;
	}
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
		return (3); //memory error
	if (init_shlvl(m))
		return (3);
	return (0);
	
}