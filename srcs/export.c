#include "minishell.h"
//finds the : in env
int	until_dquotes(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if (line[i] == '=')
			return (i);
		i++;
	}
	return (-1); // strerror env baddly config tbh
}
// return the line corresponding to the $variable 

int	find_env(char **env, char *key)
{
	int i;
	int dq;
	i = 0;

	while(env[i])
	{
		dq = until_dquotes(env[i]);
		if (!ft_strncmp(key, env[i], dq))
			return (i);
		i++;
	}
	return (-1);
}
// format the key and the value to put in cenv

char	*pair_value_key(char *value, char *key)
{
	int i;
	int j;
	int size;
	char *ret;

	i = 0;
	j = 0;
	size = ft_strlen(value) + ft_strlen(key) + 2;
	if (!(ret = malloc(sizeof(char) * size)))
		return (NULL);
	while (key[i])
		ret[j++] = key[i++];
	ret[j++] = '=';
	i = 0;
	while (value[i])
		ret[j++] = value[i++];
	ret[j] = 0;
	return (ret);
}
// get the value associated with "$key" variable

char	*getvar(char **env, char *key)
{
	int nline;
	
	signal(SIGINT, var_handler);
	nline = find_env(env, key);
	if (nline == -1)
		return "";
	else
		return (&env[nline][until_dquotes(env[nline]) + 1]);
}
// export seems okay need testing
// if no = seems not to esport anything need fixing
int	ft_export(t_mshl *m)
{
	int temp;
	int i;
	char *tempc;

	i = 1;
	while (m->args[i])
	{
		if (find_env(m->cenv, m->args[i]) == -1)
		{
			if (!(tempc = ft_strdup(m->args[i])))
				return (0);
			m->cenv = ft_append(m->cenv, tempc); // append chelou add maloc prot
		}
		else
		{	
			temp = find_env(m->cenv, m->args[i]);
			free(m->cenv[temp]);
			if(!(m->cenv[temp] = ft_strdup(m->args[i])))
				return (0);
		}
		i++;
	}
	return (1);
}

