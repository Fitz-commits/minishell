#include "minishell.h"
//finds the : in env
int	until_dquotes(char *line)
{
	int i;
	
	i = 0;
	while(line[i])
	{
		if (i == '=')
			return (i + 1);
		i++;
	}
	return (-1); // strerror env baddly config tbh
}
// return the line corresponding to the $variable 

int	find_env(char **env, char *key)
{
	int i;
	i = 0;
	
	while(env[i])
	{
		if (ft_strncmp(key, env[i], until_dquotes(env[i])))
			return (i);
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
	nline = find_env(env, key);
	if (nline == -1)
		return "";
	else
		return (&env[nline][until_dquotes(env[nline]) + 1]);
}
// export seems okay need testing
char **export(t_mshl *m, char *key, char *value)
{
	int temp;
	if (find_env(m->cenv, key) == -1)
		m->cenv = ft_append(m->cenv, pair_value_key(value,key)); // append chelou
	else
	{	temp = find_env(m->cenv, key);
		free(m->cenv[temp]);
		m->cenv[temp] = pair_value_key(value,key);
	}
	return (m->cenv);
}

