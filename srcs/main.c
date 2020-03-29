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
	if (!(m->args = ft_splitq(reader, ' ')))
		return (free_str(&reader, 1));  //recolter msg erreur
	m->nb_args = tablen(m->args);
	return (free_str(&reader, 1));
}

int		choice_command(t_mshl *m) //Check quelle commande est recue et redirige vers la fonction adequate
{
	if (!m->nb_args)
		return (2); 		//code a modifier si pas arguments juste rien faire
	else if (!ft_strcmp(m->args[0], "echo"))
		return (ft_echo(m));
	else if (!ft_strcmp(m->args[0], "exit"))
		return(0); 			//code a modifier ici il retourne 0 pour exit
	return (1); 			//a modifier juste pour return pour l'instant
}

void	ft_init(t_mshl *m)  //initialise la structure
{
	m->args = NULL;
	m->nb_args = 0;
}

int		main()
{
	t_mshl	m;		//Struct globale pour l'instant
	int		test;

	m.prompt = "Minishell$> ";
	test = 1;
	ft_init(&m);
	while (test)
	{
		write(1, m.prompt, 12);
		if (!get_args(&m))		//Recuperation des args sous forme de char** dans m->args
			return (ft_exit(&m, 1));
		if (!choice_command(&m))   //!!recup du retour a modifier pour envoyre msg erreurs etc!!
			return(ft_exit(&m, 0));
	}
	return (0);
}