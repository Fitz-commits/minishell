#include "minishell.h"

int zeroing_pipes(t_mshl *m)
{
    int i;

    i = 0;
    while (i < 512)
    {
        m->tpiped[i][0] = 0;
        m->tpiped[i][1] = 0;
        i++;
    }
    m->cp = -1;
    return (0);
}

int close_pipes(t_mshl *m)
{
    int i;

    i = 0;
    while (i < 512)
    {
        if (m->tpiped[i][0])
        {
            if ((close(m->tpiped[i][0]) == -1))
                return (-1);
            m->tpiped[i][0] = 0;
        }
        if (m->tpiped[i][1])
        {
            if ((close(m->tpiped[i][1]) == -1))
                return (-1);
            m->tpiped[i][1] = 0;
        }
        i++;
    }
    m->cp = -1;
    return (0);
}
int zeroing_process(t_mshl *m)
{
    int i;

    i = -1;
    while (++i < 512)
        m->proc.child_pid[i] = 0;
    m->proc.curpro = 0;
    return (1);
}

int     init_ptf(int (*pt_f[6])(t_mshl*))
{
    pt_f[0] = ft_echo;
    pt_f[1] = env;
    pt_f[2] = ft_unset;
    pt_f[3] = ft_cd;
    pt_f[4] = ft_export;
    //exit when working m->pt_f[5]
    return (0);
}

int waiter(t_mshl *m)
{
    int i;
    int o;

    i = -1;

    while(++i < m->proc.curpro)
    {
        //printf("m->proc.child_pid[%d] = %d\n", i, m->proc.child_pid[i]);
        waitpid(m->proc.child_pid[i], &o, 0);
        if (m->rvalue != WEXITSTATUS(o))
            if (reat_crval(m, WEXITSTATUS(o)))
                return (1);
        m->proc.child_pid[i] = 0;
    }
    m->proc.curpro = 0;
    return (0);
}
