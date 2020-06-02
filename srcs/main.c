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

int		get_args(t_mshl *m) 
{
	char	*reader;

	get_next_line(0, &reader);
	if (!(m->args = parse_cli(reader)))
		return (free_str(&reader, 1));  //recolter msg erreur
	if (!(check_for_exp(m)))
		return (free_str(&reader, 1));
	check_for_qr(m);
	print_tab(m->args);
	m->nb_args = tablen(m->args);
	
	return (free_str(&reader, 1));
}

int		choice_command(t_mshl *m) //Check quelle commande est recue et redirige vers la fonction adequate
{
	if (!m->args || !m->args[0])
		return (2); 		//code a modifier si pas arguments juste rien faire
	else if (!ft_strcmp(m->args[0], "echo"))
		return (ft_echo(m));
	else if (!ft_strcmp(m->args[0], "env"))
		return (env(m));
	else if (!ft_strcmp(m->args[0], "export"))
		return (ft_export(m));
	else if (!ft_strcmp(m->args[0], "cd"))
		return (ft_cd(m));
	else if (!ft_strcmp(m->args[0], "exit"))
		return (0);
	else if (!ft_strcmp(m->args[0], "unset"))
		return (ft_unset(m));
	else
		return (launch_exec(m, getvar(m->cenv, "PATH")));
	return (1); 			//a modifier juste pour return pour l'instant
}

void	ft_init(t_mshl *m)  //initialise la structure
{
	m->args = NULL;
	m->nb_args = 0;
	m->tstdout = 1;
}

int		main(int ac, char **av, char **envp)
{
	t_mshl	m;		//Struct globale pour l'instant
	(void)av;
	(void)ac;

	//signal(SIGINT, SIG_IGN);
	m.prompt = "minishell$> ";
	ft_init(&m);
	m.cenv = ft_getenv(envp);
	while (1)
	{
		display_prompt(&m);
		signal(SIGINT, SIG_IGN);
		if (!get_args(&m))		//Recuperation des args sous forme de char** dans m->args
			return (ft_exit(&m, 1));
		if (!choice_command(&m))   //!!recup du retour a modifier pour envoyre msg erreurs etc!!
			return(ft_exit(&m, 1));
	}
	return (0);
}
