#include "minishell.h"

/*
** To do list :
**  first capturing the key
**  getting the variable
**  Needs to remove $untilspace or ${brackets}
**
**
**  With remove in char i just need to shift every char to size on the left from pos
**
*/

char *remove_in_str(char *str, int pos, int size, int *l)
{
    int i;
    int j;

    j = 0;
    i = -1;
    while (str[pos + *l + size + ++i])
    {
        if (str[pos + *l + size + i] == '}' && *l && !j)
        {
            j = 1;
            continue;
        }
        str[pos + i - j] = str[i + pos + size + *l];
    }
    *l = 0;
    str[pos + i - j] = 0;
    return (str);
}

char *insert_into_string(char *str, char *to_insert, int pos)
{
    char    *ret;
    int     m;

    m = ft_strlen(str) + ft_strlen(to_insert) + 1;
    if (!(ret = malloc(sizeof(char) * m)))
        return (NULL);
    
    ft_bzero(ret, m);
    if (pos > 0)
        ret = ft_strncpy(ret, str, pos);
    ret = ft_strcat(ret, to_insert);
    ret = ft_strcat(ret, &str[pos]);
    free(str);
    return (ret);
}

char *env_expansion(char **line, t_mshl *m, int j, int l)
{
    int i;
    int pos;
    char buf[1000];
    char *ret;

    i = 0;
    ret = *line;
    while (ret[i])
    {
        j = 0;
        while (ret[i] && ret[i] != '$' && (i == 0 || ret[i - 1] != '\\'))
            i++;
        pos = i++;
        if (!ret[i] || ret[i] == ' ' || ret[i] == '$')
            continue;
        if (ret[i] == '{' && !(l++))
            i++;
        while (ret[i] && ret[i] != ' ' && ret[i] != '"' && ret[i] != '\'' && ret[i] != '}' && ret[i] != '$')
            buf[j++] = ret[i++];
        buf[j] = 0;
        remove_in_str(ret, pos, j + 1, &l);
        if (!(ret = insert_into_string(ret, getvar(m, buf), pos)))
            return (ret); // might want to do better than that
        printf("%s\n", ret);
        i = i - j + ft_strlen(getvar(m, buf)) - 1;
    }
    return (ret);
}

char	*catch_key(char *str, int *to_erase)
{
	int l;
	char *ret;

	l = 0;
	*to_erase = 1;
	while(str[*to_erase])
	{
		if (str[*to_erase] == '{'|| str[*to_erase] == '}')
			l += 1;
		if (str[*to_erase] && str[*to_erase] != '$' && (ft_isalnum(str[*to_erase]) || str[*to_erase] == '{'||
		str[*to_erase] == '}'|| str[*to_erase] == '?'|| str[*to_erase] == '_'))
			*to_erase += 1;
		else
			break;
		if (str[*to_erase] == '}' || str[*to_erase] == '?' || (ft_isdigit(str[*to_erase]) && *to_erase == 1))
			break;
	}
	if (l == 2)
		l = 1;
	if (!(ret = ft_strndup(&str[l + 1], *to_erase - l - 1)))
		return (NULL);
	return (ret);
}

int assemble_string(t_mshl *m, char *buffer, int to_erase)
{
	char *ret;
	int total_len;
	int i;

	i = -1;
	total_len = ft_strlen(m->reader) + ft_strlen(getvar(m, buffer)) - to_erase;
	if (!(ret = malloc(sizeof(char) * (total_len + 2))))
		return (set_err(m, 1, 0, strerror(ENOMEM)));
	while (++i < m->pos)
		ret[i] = m->reader[i];
	ft_strcpy(&ret[i], getvar(m,buffer));
	i += ft_strlen(getvar(m, buffer));
	while(i < total_len &&  m->reader[m->pos + to_erase])
	{
		ret[i++] = m->reader[m->pos + to_erase++];
	}
	ret[i] = 0;
	free(m->reader);
	m->reader = ret;
	return (EXIT_SUCCESS);
}

int		env_expension(t_mshl *m)
{
	int i;
	int flag;
	int to_erase;
	char *buffer;

	flag = 0;
	i = 0;
	while(m->reader)
	{	
		m->pos = 0;
		if ((m->reader[i] == '$' && (flag == 0 || flag == 2)))
		{
            if(!(buffer = catch_key(&m->reader[i], &to_erase)))
				return (set_err(m, 1, 0, strerror(ENOMEM)));
			m->pos = i;
			if (assemble_string(m, buffer, to_erase))
				return (free_str(&buffer, EXIT_FAILURE));
			i += ft_strlen(getvar(m, buffer));
			free(buffer);
		}
		else
			i++;
		if (!m->reader[i])
			break;
		flag = set_quotes(flag, m->reader[i]);
	}
	return (EXIT_SUCCESS);
}

int check_lee(char *line)
{
    int flag;
    int i;

    i = -1;
    flag = 0;
    while (line[++i])
    {
        if ((line[i] == '$' && (flag == 0 || flag == 2)))
            return (1);
        flag = set_quotes(flag, line[i]);
    }
    return (0);
}

int check_for_exp(t_mshl *m)
{
    if (check_lee(m->reader))
        if ((env_expension(m)))
            return (set_err(m, 1, 0, strerror(ENOMEM)));
    return (EXIT_SUCCESS);
}
