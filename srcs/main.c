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
** TODO alias dans le .h
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
				!ft_strncmp(&str[i], "<>", 2) || !ft_strncmp(&str[i], ">>>", 2))
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
		return (-1); // refaire les retours   `                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
	if (!(m->args = parse_cli(reader)))
		return (free_str(&reader, 1));  //recolter msg erreur
	//printf("\n-- Tests\n-------------\n");
	//print_tab(m->args);
	//printf("-------------\n");
	m->nb_args = tablen(m->args);
	return (free_str(&reader, 0));
}*/

int		get_args(t_mshl *m) 
{
	char	*reader;

	reader = NULL;
	if (get_next_line(0, &reader) < 0)
		return (-1);  //a faire : gérer si on a 0 de kill prog mais pas error?
	if ((m->err = first_parsing(reader)))
		return (free_str(&reader, m->err));
	if (!(m->args = parse_cli(reader)))
		return (free_str(&reader, 3));  //3 = memory error | faire les alias .h 
	if ((check_for_exp(m)))
		return (free_str(&reader, 3));
	if (check_for_qr(m))
		return (free_str(&reader, 3));
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
		return (0); 		//code a modifier si pas arguments juste rien faire
	if (n >= 0 && n <= 4)
		return (pt_f[n](m));
	else if (!ft_strcmp(m->cpargs[0], "exit"))
		exit(0);
	else if (!ft_strcmp(m->cpargs[0], "^D"))
		exit(0);
	else
		return (launch_exec(m, getvar(m, "PATH")));
	//a modifier juste pour return pour l'instant
}

int		prep_rv(t_mshl *m)
{
	if (!(m->crvalue = malloc(sizeof(char) * 10)))
		return (1);
	reat_crval(m, 0);
	return (0);
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
	m->buf_cmd = NULL;
	m->progr = 0;
	m->begin = 0;
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
** Ancien main au cas où
**

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
		if (!m.buf_cmd)
			{
				display_prompt();
				if (get_args(&m))
					return (ft_exit(&m, 1));
				if (check_for_dc(m.args) && m.args[check_for_dc(m.args) + 1])
					if (!(m.buf_cmd = fill_buffer(&m, check_for_dc(m.args))))
						return (ft_exit(&m, 1));
			}
		else
		{
			buffer_to_args(&m);
		}
		if (m.args)
		{
			if (check_for_qr(&m))
				return (ft_exit(&m, 1));
			if ((check_for_exp(&m)))
				return (ft_exit(&m, 1));
			if (set_stdior(&m) == -1)   //!!recup du retour a modifier pour envoyre msg erreurs etc!!
				return(ft_exit(&m, 0));
			//waiter(&m);
			//cleaning if an error occur we need to call those function to reset the shell
			set_zpb(&m);
			clear_std(&m);
			close_pipes(&m);
			clean_args(&m);
		}
		
	}
	return (0);
}
*/

int		ft_error(t_mshl *m)
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
	if (!m->buf_cmd)
	{
		display_prompt();
		if ((m->err = get_args(m)))
			return (ft_error(m));
		if (check_for_dc(m->args) && m->args[check_for_dc(m->args) + 1])
			if ((m->err = fill_buffer(m, check_for_dc(m->args))))
				return (ft_error(m)); //a voir pour num retour
	}
	else
	{
		buffer_to_args(m);
	}
	if (m->args)
	{
		if (set_stdior(m) == -1)
			return (-1);
		set_zpb(m);
		clear_std(m);
		close_pipes(m);
		clean_args(m);
	}
	//waiter(m);
	//if (m->cpargs)
	//	free(m->cpargs);
	//m->cpargs = NULL;
	return (0);
}

int		main(int ac, char **av, char **envp)
{
	t_mshl	m;		//Struct globale
	int		ret;
	(void)av;
	(void)ac;
	

	signal(SIGINT, handler);
	//m.prompt = "minishell$> ";
	if (prep_rv(&m))
		return (1);
	ft_init(&m);
	m.cenv = ft_getenv(envp);
	while (1)
	{
		if ((ret = main_loop(&m) < 0))
			return (ft_exit(&m, ret)); //code erreur -1 en cas d'erreur ?
	}
	return (0);
}
