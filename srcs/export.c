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

char	*getvar(t_mshl *m, char *key)
{
	int nline;
	
	signal(SIGINT, var_handler);
    signal(SIGQUIT, var_handler);
	if (key[0] == '?')
		return (m->crvalue);
	nline = find_env(m->cenv, key);
	if (nline == -1)
		return "";
	else
		return (&m->cenv[nline][until_dquotes(m->cenv[nline]) + 1]);
}

int		parse_args(char *str)
{
	int i;

	i = 0;
	if (!ft_strlen(str))
		return (9); //Not a valid identifier
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (9);
		i++;
	}
	return (0);
}

int		printexp(t_mshl *m)
{
	char	**tab;
	int		i;

	i = 0;
	if (!(tab = tabdup(m->cenv)))
		return (3); // memory error;
	sort_tab(tab);
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", m->tstdout);
		ft_putendl_fd(tab[i], m->tstdout);
		i++;
	}
	free_tab(tab, 0, 1);
	return (0);
}

int		is_equ(char *str)  //bool, return 0 if we have a = or 1 if not
{
	int i;

	if (str)
	{
		while (str[i])
		{
			if (str[i] == '=')
				return (0);
			i++;
		}
	}
	return (1);
}

// export seems okay need testing
// if no = seems not to esport anything need fixing
int	ft_export(t_mshl *m)
{
	int temp;
	int i;
	char *tempc;

	i = 1;
	//printf("\nARGS |%d|\n", m->nb_args);
	if (m->nb_args == 1)
	{
		if (printexp(m))
			return (3); //memory error
	}
	else
	{
		while (m->args[i])
		{
			if (!parse_args(m->args[i]))
			{
				if (!is_equ(m->args[i]))
				{
					if (find_env(m->cenv, m->args[i]) == -1)
					{
						if (!(tempc = ft_strdup(m->args[i])))
							return (EXIT_FAILURE);
						m->cenv = ft_append(m, tempc); // append chelou add maloc prot
					}
					else
					{	
						temp = find_env(m->cenv, m->args[i]);
						free(m->cenv[temp]);
						if(!(m->cenv[temp] = ft_strdup(m->args[i])))
							return (EXIT_FAILURE);
					}
				}
			}
			else
			{
				m->errarg = i;
				m->err = 9;
				ft_error(m);
				m->err = -10;
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

