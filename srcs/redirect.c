#include "minishell.h"

int is_redir(char *line)
{
    if (!ft_strcmp(line, "<"))
        return (1);
    else if (!ft_strcmp(line, ">"))
        return (2);
    else if (!ft_strcmp(line, "|"))
        return (5);
    else if (!ft_strcmp(line, ";"))
        return (5);
    else
        return(0);
}

/*
** This function looks for redirection
** 1 is equal to input redirection
** 2 is equal to output redirection
** 3 is equal to output redirection >>
** 4 is equal to pipe
**      which means redirecting output of first command into input of next command
*/

/*
** cette fonction permet est la fonction qui progresse dans la liste
** d'argument et permet de voir quel type de redirection il s'agit
** traite aussi le ;
** dès qu'il y a une redirection elle renvoie la valeur a la boucle
** principale qui gere au cas par cas
*/

int		check_red(t_mshl *m, int red)
{
    if (m->redir == 5)
        return (4);
    while (m->args[m->progr] && !red)
    {
        red = is_redir(m->args[m->progr]);
        if (qr_line(m))
            return (-1);
        if (red && (!m->args[m->progr + 1] || (m->progr == 0 && 
        !ft_strcmp(m->args[m->progr], "|")) || (is_redir(m->args[m->progr + 1]) 
        && ft_strcmp(m->args[m->progr + 1], ">"))))
            return (err_redir(m));
        if (!red)
            m->cpargs[m->curs++] = m->args[m->progr];
        m->progr++;
    }
    if (red == 2 && m->args[m->progr] && !ft_strcmp(m->args[m->progr], ">"))
    {
        if (!(m->args[m->progr + 1]) || is_redir(m->args[m->progr + 1]))
            return (err_redir(m));
        red = 3;
        m->progr++;
    }
    return (red);
}

/*
** fonction que l'on fait boucler dans le main pour progresser dans
** m->args et permet de rediriger le cas echeant
** lance la commande quand il n'y a plus de redirection ou quand
** ; ou quand on a besoin de l'output d'une commande pour lancer dans
** l'input du prochain (|)
** remarque pour les pipes, ls > lol | wc ne redirige pas la fonction ls dans le pipe a voir
** TODO check for segfault
** TODO remontee des erreurs
** TODO peut etre append la fin d'une ligne apres > < car peut etre argument de la fonction a lancer
** TODO gerer les pipes
** TODO fractionner cette fonction
*/

int set_progr_tabl(t_mshl *m)
{
    int i;

    i = 0;
    while (m->args[i])
        i ++;
    m->progr = i;
    return (0); 
}

int     init_ptfr(int (*pt_f[6])(t_mshl*))
{
    pt_f[0] = set_progr_tabl;
    pt_f[1] = set_stdin;
    pt_f[2] = set_stdout;
    pt_f[3] = set_stdouta;
    pt_f[4] = set_apipes;
    pt_f[5] = set_bpipes;
    return (0);
}

/*
** Open to discussion we might want to check something else than errno
** In c programming looking at errno without safefailing fonction is 
** Not usual but since we program a shell we might need to make it as is
**
*/
int handle_cpargs(t_mshl *m, int (*pt_fr[6])(t_mshl *m))
{
    while ((m->nb_args > m->progr && m->args[m->progr]) || m->cpargs[0])
    {
        if ((m->redir == 0 || m->redir == 4) && (errno || m->err))
            handle_error(m);
        else if (errno || m->err)
            reat_crval(m, 0);
        else
            reat_crval(m, 0);
        if ((m->redir = check_red(m, 0)) == -1)
            break ;
        if (m->redir >= 0 && m->redir <= 6 && (!errno ||
        m->redir == 5 || m->redir == 4))
            if (pt_fr[m->redir](m))
                break ;
        if ((m->redir == 5 || m->redir == 0) && !m->err && !errno)
        {
            choice_command(m);
            reset_cpargs(m);
        }
        if (m->redir != 5 && m->redir != 4)
          waiter(m);
    }
    return (EXIT_SUCCESS);
}

int set_stdior(t_mshl *m)
{
    int		(*pt_fr[6])(t_mshl*);

    init_ptfr(pt_fr);
    if (!(m->cpargs = malloc(sizeof(char*) * (m->nb_args + 1))))
        m->nb_args = 0;
    reset_cpargs(m);
    handle_cpargs(m, pt_fr);
    if (errno || m->err)
        handle_error(m);
    else
        reat_crval(m, 0);
    return (EXIT_SUCCESS);
}

/*
** 
** There is a problem with this the command :
**  ls > lol lol
**  send lol as a parameter to ls might need to check after file 
**  specification to see if there is a valid thing to add to the
**  command as a parameter
*/
