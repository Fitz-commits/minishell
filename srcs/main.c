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
** ajout de differentes fonction qui permettent
** le quote_removal et l'env expansion
** 
** TODO remontee d'erreur
** TODO pour la fin pas oublier de retirer / modifier les printf + virer splitq2
**
*/

int		get_args(t_mshl *m) 
{
	char	*reader;

	reader = NULL;
	get_next_line(0, &reader);
	if (!(m->args = parse_cli(reader)))
		return (free_str(&reader, 1));  //recolter msg erreur
	if (!(check_for_exp(m)))
		return (free_str(&reader, 1));
	check_for_qr(m);
	//printf("\n-- Tests\n-------------\n");
	print_tab(m->args);
	//printf("-------------\n");
	m->nb_args = tablen(m->args);
	return (free_str(&reader, 1));
}

/*
** ici on n'envoie plus m->args on envoi une copie
** cette copie n'a plus les elements < > | ; car on ne peut envoyer ce genre
** d'argument
**
** TODO remontee d'erreur
** TODO fractionner la fonction
** TODO leaks sur le free cpargs
** close_rp to add
*/
int		prep_cpargs(t_mshl *m)
{
	if (m->cpargs)
		free(m->cpargs); //Redondant ?
	m->cpargs = NULL;
	if (!(m->cpargs = cpy_args(m->args, m->begin, next_split(m))))
		return (EXIT_FAILURE);
	m->begin = m->progr;
	return (0);
	}
int		choice_command(t_mshl *m) //Check quelle commande est recue et redirige vers la fonction adequate
{
	int		(*pt_f[6])(t_mshl*);
	int		n;

	init_ptf(pt_f);
	if (prep_cpargs(m))
		return (EXIT_FAILURE);
	n = n_command(m);
	//print_tab(m->cpargs); // debugging only
	if (!m->cpargs)
		return (2); 		//code a modifier si pas arguments juste rien faire
	if (n >= 0 && n <= 4)
		return (pt_f[n](m));
	else if (!ft_strcmp(m->cpargs[0], "exit"))
		exit(0);
	else if (!ft_strcmp(m->cpargs[0], "^D"))
		return (EXIT_SUCCESS);
	else
		return (launch_exec(m, getvar(m->cenv, "PATH")));
	//a modifier juste pour return pour l'instant
}

void	ft_init(t_mshl *m)  //initialise la structure
{
	m->args = NULL;
	m->cpargs = NULL;
	m->nb_args = 0;
	m->tstdin = 0;
	m->tstdout = 1;
	//m->tstderr = 2;
	m->redir = 0;
	zeroing_pipes(m);
	zeroing_process(m);
}

void set_zpb(t_mshl *m)
{
	m->progr = 0;
	m->begin = 0;
}


/*
** TODO regarder boucle infinie du ctrl d !!
**
*/ 
int		main(int ac, char **av, char **envp)
{
	t_mshl	m;		//Struct globale pour l'instant
	(void)av;
	(void)ac;

	signal(SIGINT, handler);
	//m.prompt = "minishell$> ";
	ft_init(&m);
	m.cenv = ft_getenv(envp);
	while (1)
	{
		display_prompt();
		set_zpb(&m);
		if (!get_args(&m))		//Recuperation des args sous forme de char** dans m->args
			return (ft_exit(&m, 1));
		if (set_stdior(&m) == -1)   //!!recup du retour a modifier pour envoyre msg erreurs etc!!
			return(ft_exit(&m, 0));
		waiter(&m);
		clear_std(&m);
		if (m.cpargs)
			free(m.cpargs);
		m.cpargs = NULL;
		close_pipes(&m);
	}
	return (0);
}
