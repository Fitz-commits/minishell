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
** TODO virer le err += 1 dans redirect.c mis pour la compilation
*/

int		first_parsing(char *str)
{
	int i;
	int q;

	i = 0;
	q = 0;
	while (str[i])
	{
		q = set_quotes(q, str[i]);
		if (!q)
		{
			if (str[i] == '*' || !ft_strncmp(&str[i], "&&", 2) ||
				!ft_strncmp(&str[i], "||", 2) || !ft_strncmp(&str[i], "<<", 2))
				return (1); // not implemented
			if (str[i] == '&' || !ft_strncmp(&str[i], "<|", 2) ||
				!ft_strncmp(&str[i], "|<", 2) || !ft_strncmp(&str[i], ">|", 2) ||
				!ft_strncmp(&str[i], "|>", 2) || !ft_strncmp(&str[i], "><", 2) ||
				!ft_strncmp(&str[i], "<>", 2))
				return (2); //Parsing error
		}
		i++;
	}
	return (0);
}
 
/*int		get_args(t_mshl *m) 
{
	char	*reader;

	reader = NULL;
	if (!get_next_line(0, &reader))
		return (0);
	// first parsing
	if (first_parsing(reader))
		return (-1); // refaire les retours                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
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
}*/

int		get_args(t_mshl *m) 
{
	char	*reader;

	reader = NULL;
	if (get_next_line(0, &reader) < 1)
		return (-1);  //a faire : gérer si on a 0 de kill prog mais pas error?
	if ((m->err = first_parsing(reader)))
		return (free_str(&reader, m->err));
	if (!(m->args = parse_cli(reader)))
		return (free_str(&reader, 3));

	if (!(check_for_exp(m)))
		return (free_str(&reader, 1));
	check_for_qr(m);
	//printf("\n-- Tests\n-------------\n");
	print_tab(m->args);
	//printf("-------------\n");
	m->nb_args = tablen(m->args);
	return (free_str(&reader, 0));
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
		return (launch_exec(m, getvar(m, "PATH")));
	//a modifier juste pour return pour l'instant
}

void	ft_init(t_mshl *m)  //initialise la structure might want to failproof it now that it malloc's
{
	m->args = NULL;
	m->cpargs = NULL;
	m->nb_args = 0;
	m->tstdin = 0;
	m->tstdout = 1;
	//m->tstderr = 2;
	m->redir = 0;
	m->rvalue = 0;
	m->crvalue = ft_itoa(0);
	m->error = 0;
	m->err = 0;
	zeroing_pipes(m);
	zeroing_process(m);
}

void	set_zpb(t_mshl *m)
{
	m->progr = 0;
	m->begin = 0;
	m->error = 0;
}

/*
int		main(int ac, char **av, char **envp)
{
	t_mshl	m;		//Struct globale pour l'instant
	(void)av;
	(void)ac;
	int tmp; //partira après gestion erreurs

	signal(SIGINT, handler);
	//m.prompt = "minishell$> ";
	ft_init(&m);
	m.cenv = ft_getenv(envp);
	while (1)
	{
		display_prompt();
		set_zpb(&m);   //a voir pour mettre dans ft_init
		if ((tmp = get_args(&m)) <= 0)		//Recuperation des args sous forme de char** dans m->args
		{
			if (tmp < 0)
			{
				write(2, "parsing error\n", 14);
				continue;
			}
			else if (!tmp)
				return (ft_exit(&m, 1));
		}
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
}*/

int		ft_error(t_mshl *m, int err)
{
	if (m->error)
	{
		ft_putendl_fd(strerror(m->error), 2);
		return (m->error);
	}
	(m->err == 1) ? ft_putendl_fd("Not Implemented", 2) : 0;
	(m->err == 2) ? ft_putendl_fd("Parsing Error", 2) : 0;
	(m->err == 3) ? ft_putendl_fd("Memory Error", 2) : 0;
	return (m->err);
}

int		main_loop(t_mshl *m)
{
	set_zpb(m);
	if ((m->err = get_args))
		return (ft_error(m));
	if (set_stdior(m) == -1)
		return (-1);
	waiter(m);
	clear_std(m);
	if (m->cpargs)
		fee(m->cpargs);
	m->cpargs = NULL;
	close_pipes(m);
}

int		main(int ac, char **av, char **envp)
{
	t_mshl	m;		//Struct globale
	(void)av;
	(void)ac;

	signal(SIGINT, handler);
	//m.prompt = "minishell$> ";
	ft_init(&m);
	m.cenv = ft_getenv(envp);
	while (1)
	{
		display_prompt();
		if (main_loop(&m) < 0)
			return (ft_exit(&m, -1)) //code erreur -1 en cas d'erreur ?
	}
	return (0);
}
