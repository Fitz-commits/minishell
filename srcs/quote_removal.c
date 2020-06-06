#include "minishell.h"

int     check_quotes(char *line)
{
    int i;
    int flag;

    i = -1;
    flag = 0;
    while (line[++i])
    {
        flag = set_quotes(flag, line[i]);
        if (flag)
            return (1);
    }
    return (0);
}
int     count_aqr(char *line)
{
    int i;
    int j;
    int flag;

    i = -1;
    flag = 0;
    j = 0;
    while (line[++i])
    {
        flag = set_quotes(flag, line[i]);
        if ((flag == 2 || flag == 0) && line[i] == '"')
            continue;
        if ((flag == 1 || flag == 0) && line[i] == '\'')
            continue;
        if (((flag == 0 || flag == 2)) && line[i] == '\\')
            continue;
        j++;
    }
    return (j);
}
char *remove_quotes(char *line, int j)
{
    int i;
    int flag;
    int pass;
    char *ret;

    i = -1;
    j = 0;
    flag = 0;
    if (!(ret = malloc(sizeof(char) * (count_aqr(line) + 1))))
        return (NULL);
    while (line[++i])
    {
        pass = 0;
        pass = (pass || ((flag == 2 || flag == 0) && line[i] == '"')) ? 1 : 0;
        pass = (pass || ((flag == 1 || flag == 0) && line[i] == '\'')) ? 1 : 0;
        pass = (pass || (((flag == 0 || flag == 2)) && line[i] == '\\')) ? 1 : 0;
        flag = set_quotes(flag, line[i]);
        if (!pass)
            ret[j++] = line[i];
    }
    free(line);
    ret[j] = 0;
    return (ret);
}

int check_for_qr(t_mshl *m)
{
    int i;
    i = -1;

    while (m->args[++i])
        if (check_quotes(m->args[i]))
            if (!(m->args[i] = remove_quotes(m->args[i], 0)))
                return (1);
    return (0);
}