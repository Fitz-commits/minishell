/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:49:37 by marvin            #+#    #+#             */
/*   Updated: 2020/03/26 16:49:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
** ces trois fonction gerent les differentes redirection au cas par
** cas et parmet l'ouverture d'un fd tout en fermant le fd precedent
** car il peut y avoir plusieurs redirection a la suite mais la derniere
** est celle prise en compte
** 
** Standardiser ces trois functions sur les erreurs 
** Ajouter une liste de symbole sur lesquel on ne cree pas de fd
** maybee that the quote reduction is happening too early
*/

int set_stdouta(t_mshl *m)
{
    int fd;

    if (m->tstdout > 1 && (m->cp < 0 || m->tstdout != m->tpiped[m->cp][1]))
    {
        close(m->tstdout);
        m->tstdout = 1;
    }
    if (qr_line(m))
        return (EXIT_FAILURE);
    if (((fd = open(m->args[m->progr],
    O_CREAT | O_WRONLY | O_APPEND, 0666)) == -1))
        return (set_err(m, 1, 1, m->args[m->progr], strerror(errno)));
    else
        m->tstdout = fd;
    m->progr++;
    return (EXIT_SUCCESS);
}

int set_stdout(t_mshl *m)
{
    int fd;

    if (m->tstdout > 1 && (m->cp < 0 || m->tstdout != m->tpiped[m->cp][1]))
    {
        close(m->tstdout);
        m->tstdout = 1;
    }
    if (qr_line(m))
        return (EXIT_FAILURE);
    if (((fd = open(m->args[m->progr], O_WRONLY | O_CREAT
		| O_TRUNC , 0666)) < 0))
        return (set_err(m, 1, 1, m->args[m->progr], strerror(errno)));
    m->tstdout = fd;
    m->progr++;
    return (EXIT_SUCCESS);
}

int set_stdin(t_mshl *m)
{
    int fd;

    if (m->tstdin && (m->cp < 0 || m->tstdin != m->tpiped[m->cp][0]))
    {
        m->tstdin = close(m->tstdin);
        m->tstdin = 0;
    }
    if (qr_line(m))
        return (EXIT_FAILURE);
    if ((fd = open(m->args[m->progr], O_RDONLY)) == -1)
        return (set_err(m, 1, 1, m->args[m->progr], strerror(errno)));
    m->tstdin = fd;
    m->progr++;
    return (EXIT_SUCCESS);
}

int set_apipes(t_mshl *m)
{
    if (m->tstdin  && (m->cp < 0 || m->tstdin != m->tpiped[m->cp - 1][0]))
        close(m->tstdin);
    m->tstdin = m->tpiped[m->cp][0];
    m->tstdout = 1;
    ft_bzero(m->cpargs, sizeof(char*) * (m->nb_args + 1));
    m->curs = 0;
    return(0);
}

int set_bpipes(t_mshl *m)
{
    int err;

    m->cp++;
    err = pipe(m->tpiped[m->cp]);
    if (m->tstdout == 1 || (m->cp > 0 && m->tstdout == m->tpiped[m->cp - 1][1]))
        m->tstdout = m->tpiped[m->cp][1];
    return (err);
}
