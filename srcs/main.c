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
*/

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
        ft_exit(m, 0); 
	if ((m->err = first_parsing(m, m->reader)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** ici on n'envoie plus m->args on envoi une copie
** cette copie n'a plus les elements < > | ; car on ne peut envoyer ce genre
** d'argument
**
*/

int		choice_command(t_mshl *m)
{
	int		(*pt_f[6])(t_mshl*);
	int		n;

	init_ptf(pt_f);
	m->cpargs[m->curs] = 0;
	m->nb_cpargs = tablen(m->cpargs);
	n = n_command(m);
	if (!m->cpargs)
		return (0);
	if (n >= 0 && n <= 5 && m->tstdout != -1)
		return (pt_f[n](m));
	else if (!ft_strcmp(m->cpargs[0], "exit"))
		return (ft_exit(m, 0));
	else if (!ft_strcmp(m->cpargs[0], "^D"))
		return (ft_exit(m, 0));
	else
		return (launch_exec(m, getvar(m, "PATH")));
}

int		main_loop(t_mshl *m)
{
	if (!m->buff_cmd)
	{
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
		m->nb_args = tablen(m->args);
		if (set_stdior(m) == -1)
			return (-1);
		reset_struct(m);
	}
	return (0);
}

int		main(int ac, char **av, char **envp)
{
	t_mshl	m;
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
			return (ft_exit(&m, ret));
        if (ac == 3 && !m.buff_cmd)
            exit(m.rvalue);
	}
	return (0);
}
