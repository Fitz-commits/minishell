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
    return str;
}

char *insert_into_string(char *str, char *to_insert, int pos)
{
    char *ret;
    
    if (!(ret = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(to_insert) + 1))))
        return (NULL);
    ret = ft_strncpy(ret, str, pos);
    ret = ft_strcat(ret, to_insert);
    ret = ft_strcat(ret, &str[pos]);
    free(str);
    return (ret);
}

char *env_expansion(char *line, t_mshl *m, int j, int l)
{
    int i;
    int pos;
    char buf[128];
    char *ret;

    i = 0;
    ret = line;
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
        printf("%s\n", buf);
        remove_in_str(ret, pos, j + 1, &l);
        if (!(ret = insert_into_string(ret, getvar(m->cenv, buf), pos)))
            return (ret); // might want to do better than that
        i = i - j + ft_strlen(getvar(m->cenv, buf)) - 1;
    }
    return (ret);
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
    int i;

    i = -1;
    while(m->args[++i])
        if (check_lee(m->args[i]))
            if (!(m->args[i] = env_expansion(m->args[i], m, 0, 0)))
                return 0;
    return (1);
}
