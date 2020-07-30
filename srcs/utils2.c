#include "minishell.h"
/*
** aprės parsing, il faudrait 
**
**
**
**
*/
int check_for_dc(char **args)
{
    int i;

    i = -1;
    if (!args)
        return (0);
    while (args[++i])
        if (!ft_strcmp(args[i], ";"))
            return (i);
    return (0);
}

// push dans le buffer ce qu'il y a apres le ; et garde dans le m->args ce qu'il y a avant

char **fill_buffer(t_mshl *m, int i)
{
    char **ret;
    int count;
    int j;

    j = 0;
    count = 1;
    while (m->args[i + count++])
        ;
    if (!(ret = malloc(sizeof(char*) * (count + 1))))
        return (NULL);
    count = i++;
    while (m->args[i])
        ret[j++] = m->args[i++];
    ret[j] = NULL;
    m->args[count] = NULL;
    //print_tab(ret);
    return (ret);
}
/*
** got the feeling that we got a leak lurking around here
**
**
**
*/
int buffer_to_args(t_mshl *m)
{
    int i;
    int j;

    i = -1;
    if ((j = check_for_dc(m->buf_cmd)))
        while (++i < j)
            m->args[i] = m->buf_cmd[i];
    else // a mettre dans une fonction
    {
        free(m->args);
        m->args = m->buf_cmd;
        m->buf_cmd = NULL;
        return (0);
    }
    free(m->buf_cmd[j]);
    m->buf_cmd[j] = NULL;
    m->args[i] = NULL;
    i = 0;
    if (!m->buf_cmd[++j])
    {
        free(m->buf_cmd);
        m->buf_cmd = NULL;
        return (0);
    }
    while (m->buf_cmd[j])
        m->buf_cmd[i++] = m->buf_cmd[j++];
    m->buf_cmd[i] = NULL;
    return (0);
}

/*
** pseudo code :
** getting into the while
** 
** if m->buf_cmd ==> buffer to args
** else get from gnl ==> parse_cli
**      if ; in args => fill_buffer
** 
*/
int clean_args(t_mshl *m)
{
    int i;

    i = 0;
    if (m->cpargs)
        free(m->cpargs);
    m->cpargs = NULL;
    while (m->args[i])
        free(m->args[i++]);
    if (!m->buf_cmd)
    {
        free(m->args);
        m->args = NULL;
    }
    return (0);
}