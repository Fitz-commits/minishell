#include "minishell.h"

int is_redir(char *line)
{
    if (!ft_strcmp(line, "<"))
        return (1);
    else if (!ft_strcmp(line, ">"))
        return (2);
    else if (!ft_strcmp(line, "|"))
        return (4);
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
int     next_split(t_mshl *m)
{
    int i;

    i = m->begin;
    if (i >= m->nb_args)
        return (0);
    while(m->args[i])
    {
        if (is_redir(m->args[i]) || !ft_strcmp(m->args[i], ";"))
            return (i);
        i++;
    }
    return(tablen(m->args));
}
/*
** cette fonction permet est la fonction qui progresse dans la liste
** d'argument et permet de voir quel type de redirection il s'agit
** traite aussi le ;
** dès qu'il y a une redirection elle renvoie la valeur a la boucle
** principale qui gere au cas par cas
*/
int		check_red(t_mshl *m)
{
    int red;

    red = 0;
    while (m->args[m->progr] && !red)
    {
        red = is_redir(m->args[m->progr]); // qr here
        m->progr++;
    }
    if (red == 2 && m->args[m->progr] && !ft_strcmp(m->args[m->progr], ">"))
    {
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

int     init_ptfr(int (*pt_f[5])(t_mshl*))
{
    pt_f[0] = set_progr_tabl;
    pt_f[1] = set_stdin;
    pt_f[2] = set_stdout;
    pt_f[3] = set_stdouta;
    pt_f[4] = set_bpipes;
    return (0);
}
void print_errno(char *str)
{
    ft_putstr_fd("minishell : ", 2);
    if (str)
        {
        ft_putstr_fd(str, 2);
        ft_putstr_fd(" : ", 2);
        }
    ft_putendl_fd(strerror(errno), 2);
}

void print_error(t_mshl *m)
{
    if (errno && !m->err)
    {
        print_errno(m->args[m->progr]);
        reat_crval(m, 1);
    }
    else if (m->err && m->err != 4)
    {
        reat_crval(m, m->err);
        (m->err == 1) ? ft_putendl_fd("Not Implemented", 2) : 0;
	    (m->err == 2) ? ft_putendl_fd("Parsing Error", 2) : 0;
	    (m->err == 3) ? ft_putendl_fd("Memory Error", 2) : 0;
        (m->err == 127) ? ft_putendl_fd("Command not found", 2) : 0;
    }
    errno = 0;
}
/*
** Open to discussion we might want to check something else than errno
** In c programming looking at errno without safefailing fonction is 
** Not usual but since we program a shell we might need to make it as is
**
*/
int set_stdior(t_mshl *m)
{
    int		(*pt_fr[5])(t_mshl*);

    init_ptfr(pt_fr);
    while (m->nb_args > m->progr && m->args[m->progr])
    {
        if (errno || m->err)
            print_error(m);
        else
            reat_crval(m, 0);
        m->redir = check_red(m);  // quote reduction here
        if ((m->progr == 1  && m->redir) || (m->progr == 2 && m->redir == 3))
            m->err = 2; // parse error might want to do this upper
        if (m->redir >= 0 && m->redir <= 4)
            if (pt_fr[m->redir](m))
            {
                m->begin = m->progr;
                continue;
            }
        if ((m->redir == 5 || m->redir == 4 || m->redir == 0))
            choice_command(m);
        if (m->redir != 4)
            waiter(m);
        if (m->redir == 4)
            set_apipes(m);
    }
    if (errno || m->err)
            print_error(m);
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
