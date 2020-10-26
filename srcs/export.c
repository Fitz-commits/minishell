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
	int j;
	char buffer[512];

	i = 0;
	ft_bzero(buffer, 512);
	while(env[i])
	{	
		j = -1;
		dq = until_dquotes(env[i]);
		while(++j < dq)
			buffer[j] = env[i][j];
		buffer[j] = 0;
		if (!ft_strcmp(key, buffer))
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

int		parse_varname(char *str)
{
	int		i;

	i = 0;
	if (!ft_strlen(str))
		return (9); //Not a valid identifier
	if ((str[i] >= 48 && str[i] <= 57) || str[i] <= '=')
		return (9);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (9);
		i++;
	}
	/*prarse_bs(str);
	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (!str[i])
		return (-1); // No = in the args, just pass
	while (str[i + 1])
	{
		if (str[i] == '\\')
		{

		}
	}*/
	return (0);
}

int		printexp(t_mshl *m)
{
	char	**tab;
	int		i;
	int		equ;

	i = 0;
	if (!(tab = tabdup(m->cenv)))
		return (3); // memory error;
	sort_tab(tab);
	while (tab[i])
	{
		equ = 0;
		ft_putstr_fd("declare -x ", m->tstdout);
		while (tab[i][equ] != '=' && tab[i][equ])
			equ++;
		equ++;
		write(m->tstdout, tab[i], equ);
		ft_putchar_fd('\"', m->tstdout);
		ft_putstr_fd(&tab[i][equ], m->tstdout);
		ft_putchar_fd('\"', m->tstdout);
		ft_putchar_fd('\n', m->tstdout);
		i++;
	}
	free_tab(tab, 0, 1);
	return (0);
}

char	*ft_cut(char *s, int end_s1, int start_s2)
{
	int i;
	char *new;

	i = 0;
	if (!(new = (char *)malloc(end_s1 + ft_strlen(&s[start_s2] + 1))))
		return (NULL);
	while (i < end_s1)
		new[i++] = s[end_s1++];
	while (s[start_s2])
		new[i++] = s[start_s2++];
	new[i] = '\0';
	return (new);
	
}

int		parse_args(t_mshl *m, int arg /*char *str*/)  //bool, return 0 if we have a = or 1 if not
{
	int		i;
	char 	*tmp;

	i = 0;
	if (m->args[arg])
	{
		while (m->args[arg][i] && m->args[arg][i] != '=')
			i++;
		if (!m->args[arg][i])
			return (-1);
		i = 0;
		while (m->args[arg][i + 1])
		{
			if (m->args[arg][i] == '\\')
			{
				tmp = m->args[arg];
				if (!(m->args[arg] = ft_cut(m->args[arg], i - 1, i + 1)))
					return (3);
				free_str(&tmp, 0);
			}
			i++;
		}
		if (m->args[arg][i] == '\\')
			return (2);
	}
	return (0);
}

// export seems okay need testing
// if no = seems not to esport anything need fixing
int	ft_export(t_mshl *m)
{
	int		temp;
	int		i;
	char	*tempc;
	int		ret;	
	
	i = 1;
	//printf("\nARGS |%d|\n", m->nb_args);
	if (m->nb_args == 1)
	{	
		if (printexp(m))
			return (3); //memory error
		return (EXIT_SUCCESS);
	}
	while (m->args[i])
	{
		if (!parse_varname(m->args[i]))
		{
			if (!(ret = parse_args(m, i)))
			{
				if (find_env(m->cenv, m->args[i]) == -1)
				{
					if (!(tempc = ft_strdup(m->args[i])))
						return (3);
					m->cenv = ft_append(m, tempc); // append chelou add maloc prot
				}
				else
				{	
					temp = find_env(m->cenv, m->args[i]);
					free(m->cenv[temp]);
					if(!(m->cenv[temp] = ft_strdup(m->args[i])))
						return (3);
				}
			}
			else if (ret > 0)
				return (2);
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
	return (EXIT_SUCCESS);
}

