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
        red = is_redir(m->args[m->progr]);
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
** ces trois fonction gerent les differentes redirection au cas par
** cas et parmet l'ouverture d'un fd tout en fermant le fd precedent
** car il peut y avoir plusieurs redirection a la suite mais la derniere
** est celle prise en compte
** TODO remontee d'erreur
** 
*/
int set_stdouta(t_mshl *m)
{
    int fd;
    if (m->tstdout != 1 && (m->cp < 0 || m->tstdout != m->tpiped[m->cp][1]))
        close(m->tstdout);
    if (!m->args[m->progr])
        return (1);
    if (((fd = open(m->args[m->progr], O_CREAT | O_WRONLY | O_APPEND, 0666)) == -1))
        return (-1);
    return (fd);

}

int set_stdout(t_mshl *m)
{
    int fd;

    if (m->tstdout != 1 && (m->cp < 0 || m->tstdout != m->tpiped[m->cp][1]))
        close(m->tstdout);
    if (((fd = open(m->args[m->progr], O_WRONLY | O_CREAT
		| O_TRUNC , 0666)) < 0))
            return (-1);
    return (fd);

}
int set_stdin(t_mshl *m)
{
    int fd;
    if (m->tstdin && (m->cp < 0 || m->tstdin != m->tpiped[m->cp][0]))
        m->tstdin = close(m->tstdin);
    if ((fd = open(m->args[m->progr], O_RDONLY)) == -1)
        return (0);
    return (fd);
}
int set_apipes(t_mshl *m)
{
    if (m->tstdin  && (m->cp < 0 || m->tstdin != m->tpiped[m->cp - 1][0]))
        close(m->tstdin);
    m->tstdin = m->tpiped[m->cp][0];
    m->tstdout = 1;
    return(0);
}

int set_bpipes(t_mshl *m)
{
    int err;

    m->cp++;
    err = pipe(m->tpiped[m->cp]);
    if (m->tstdout == 1 || (m->cp > 0 && m->tstdout == m->tpiped[m->cp - 1][1]))
        m->tstdout = m->tpiped[m->cp][1];
    return (0);

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
int set_stdior(t_mshl *m)
{
    if (!m->nb_args)
        return (0);
    while (m->nb_args > m->progr && m->args[m->progr])
    {
        m->redir = check_red(m);
        if (m->redir == 0)
            m->progr = tablen(m->args);
        if (m->redir == 1)
            m->tstdin = set_stdin(m);
        if (m->redir == 2)
            m->tstdout = set_stdout(m);
        if (m->redir == 3)
            m->tstdout = set_stdouta(m);
        if ((m->progr == 1  && m->redir) || (m->progr == 2 && m->redir == 3))
            return (0); // parse error might want to
        if (m->redir == 4)
            set_bpipes(m);
        if (m->redir == 5 || m->redir == 4 || m->redir == 0)
            choice_command(m);
        if (m->redir != 4)
            waiter(m);
        if (m->redir == 4)
            set_apipes(m);
        if (m->redir == 5) // need to clear pipes and processes
            if(clear_std(m))
                printf("error");
    }
    return (0);
}

/*
** 
** There is a problem with this the command :
**  ls > lol lol
**  send lol as a parameter to ls might need to check after file 
**  specification to see if there is a valid thing to add to the
**  command as a parameter
*/
