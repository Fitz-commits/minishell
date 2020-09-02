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
int remove_quotes(t_mshl *m, int j, int pos)
{
    int i;
    int flag;
    int pass;
    char *ret;

    i = -1;
    j = 0;
    flag = 0;
    if (!(ret = malloc(sizeof(char) * (count_aqr(m->args[pos]) + 1))))
        return (m->err = 3);
    while (m->args[pos][++i])
    {
        pass = 0;
        pass = (pass || ((flag == 2 || flag == 0) && m->args[pos][i] == '"')) ? 1 : 0;
        pass = (pass || ((flag == 1 || flag == 0) && m->args[pos][i] == '\'')) ? 1 : 0;
        pass = (pass || (((flag == 0 || flag == 2)) && m->args[pos][i] == '\\')) ? 1 : 0;
        flag = set_quotes(flag, m->args[pos][i]);
        if (!pass)
            ret[j++] = m->args[pos][i];
    }
    free(m->args[pos]);
    ret[j] = 0;
    m->args[pos] = ret;
    return (0);
}
/*
int check_for_qr(t_mshl *m)
{
    int i;
    int j;

    i = -1;
    j =0;
    while (m->args[++i])
        if (check_quotes(m->args[i]))
            if (!(m->args[i] = remove_quotes(m->args[i], 0)))
            {
                while (m->args[j] || i == j)
                    free(m->args[i]);
                free(m->args);
                m->args = NULL;
                return (EXIT_FAILURE);
            }
    return (EXIT_SUCCESS);
    }*/
