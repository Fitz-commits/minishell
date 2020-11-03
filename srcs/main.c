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
** piped double quote
*/
int check_for_pdq(t_mshl *m, char *str)
{
	int i;

	i = 0;
	if (str[0] == '|' || str[0] == ';')
	{
		m->cerr = str[0];
		return (EXIT_FAILURE);
	}
	while (str[i] && is_space(str[i]))
	{
		i++;
		if (str[i] && (str[i] == ';' || str[i] == '|'))
		{
			m->cerr = str[i];
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
int		first_parsing(t_mshl *m, char *str)
{
	int i;
	int q;
	int err;

	i = 0;
	q = 0;
	if (check_for_pdq(m, str))
		return (2);
	while (str[i])
	{
		if (!q)
		{
			err = check_pni_errors(m, str, i);
			if (err != 0)
				return (2);
		}
		q = set_quotes(q, str[i]);
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
    int ret;


    if (!m->reader)
	    ret = get_next_line(0, &m->reader);
    else
        ret = 1;
	if (ret == -1)
        return (-1);
    if (ret == 0)
    {
        free(m->reader);
        ft_exit(m, 0);
    }  //a faire : gérer si on a 0 de kill prog mais pas error?
	if ((m->err = first_parsing(m, m->reader)))
		return (free_str(&m->reader, m->err));
	 //3 = memory error | faire les alias .h 
	
	//printf("\n-- Tests\n-------------\n");
	//print_tab(m->args);
	//printf("-------------\n");
	// ======> important to make after m->nb_args = tablen(m->args);
	return (EXIT_SUCCESS);
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
int		prep_cpargs(t_mshl *m) //prend sa retraite
{
	if (m->cpargs)
		free(m->cpargs); //Redondant ?
	m->cpargs = NULL;
	if (!(m->cpargs = cpy_args(m->args, m->begin, next_split(m))))
		return (EXIT_FAILURE);
	m->nb_cpargs = tablen(m->cpargs);
	m->begin = m->progr;
	return (0);
}

int		choice_command(t_mshl *m) //Check quelle commande est recue et redirige vers la fonction adequate
{
	int		(*pt_f[6])(t_mshl*);
	int		n;

	init_ptf(pt_f);
	m->cpargs[m->curs] = 0;
	m->nb_cpargs = tablen(m->cpargs);
	n = n_command(m);
	//print_tab(m->cpargs); // debugging only
	if (!m->cpargs)
		return (0); 		//code a modifier si pas arguments juste rien faire
	if (n >= 0 && n <= 5 && m->tstdout != -1)
		return (pt_f[n](m));
	else if (!ft_strcmp(m->cpargs[0], "exit"))
		return (ft_exit(m, 0));
	else if (!ft_strcmp(m->cpargs[0], "^D"))
		return (ft_exit(m, 0));
	else
		return (launch_exec(m, getvar(m, "PATH")));
	//a modifier juste pour return pour l'instant
}

int		prep_rv(t_mshl *m)
{
	
	if (!(m->crvalue = malloc(sizeof(char) * 10)))
			return (EXIT_FAILURE);
	reat_crval(m, 0);
	return (0);
}

void	ft_init(t_mshl *m)  //initialise la structure might want to failproof it now that it malloc's
{
	ft_bzero(m->err_to_print, PATH_MAX + 1);
	m->args = NULL;
	m->cpargs = NULL;
	m->nb_args = 0;
	m->tstdin = 0;
	m->tstdout = 1;
	//m->tstderr = 2;
	m->redir = 0;
	m->rvalue = 0;
	m->buff_cmd = NULL;
	m->progr = 0;
	m->begin = 0;
	m->error = 0;
	m->err = 0;
	m->errarg = -1;  // if -1 no args print in error nsg 
	zeroing_pipes(m);
	zeroing_process(m);
}

void	set_zpb(t_mshl *m)
{
	m->progr = 0;
	m->begin = 0;
	m->error = 0;
    m->err = 0;
	m->ierr = -1;
    m->errarg = -1;
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

/*int		ft_errors(t_mshl *m)
{
	if (m->error)
	{
		ft_putendl_fd(strerror(m->error), 2);
		return (m->error);
	}
	reat_crval(m, m->err);
	(m->err == 1) ? ft_putendl_fd("Not Implemented", 2) : 0;
	(m->err == 2) ? ft_putendl_fd("Parsing Error", 2) : 0;
	(m->err == 3) ? ft_putendl_fd("Memory Error", 2) : 0;
	return (m->err);
}*/

void    free_and_null(t_mshl *m, int i) //prend sa retraite
{
    
    free(m->args[i]);
    m->args[i] = NULL;
}

int		main_loop(t_mshl *m)
{
	if (!m->buff_cmd)
	{
		//display_prompt();
		if ((m->err = get_args(m)))
			return (main_error(m));
		if ((find_dq(m->reader) >= 0))
			if ((alloc_bufcmd(m)))
				return (main_error(m));
	}
	else
	{
		if ((buf_cmd_to_args(m)))
			return (main_error(m));
	}
	if (m->reader)
	{
        if ((check_for_exp(m)))
			return (main_error(m));
		if (!(m->args = parse_cli(m->reader, m)))
			return (main_error(m));
		//print_tab(m->args);
		m->nb_args = tablen(m->args);
        //print_tab(m->args);
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

	

	signal(SIGINT, handler);
    signal(SIGQUIT, handler);
	//m.prompt = "minishell$> ";
	if (prep_rv(&m))
		return (1);
	ft_init(&m);
	if (env_init(&m, envp))
		exit(3); //modifier retour
	//m.cenv = ft_getenv(envp);
    complete_env(&m);
	set_err(&m, 2, 1,"Parsing error near", "c");
    if (ac == 3)
    {
        if (!ft_strcmp(av[1], "-c"))
            m.reader = ft_strdup(av[2]);
    }
    else
        m.reader = NULL;
	while (1)
	{
		if ((ret = main_loop(&m) < 0))
			return (ft_exit(&m, ret)); //code erreur -1 en cas d'erreur ?
        if (ac == 3 && !m.buff_cmd)
            exit(m.rvalue);
	}
	return (0);
}
