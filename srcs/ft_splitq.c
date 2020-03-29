/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 18:55:48 by marvin            #+#    #+#             */
/*   Updated: 2020/03/26 18:55:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//Split la fonction < 25 lignes
//Checker leaks

/*
** strnjoin + free tmp
*/
int		stnjf(char **s1, char *s2, int start, int len)
{
	char *tmp;

	tmp = *s1;
	if (!(*s1 = ft_strnjoin(*s1, s2, start, len)))
		free_str(&tmp, 0);
	return (free_str(&tmp, 1));
}

int		ft_in_quotes(int *i, int *j, char *s, char **str_append)
{
	int		q;

	q = s[*i];
	if (!stnjf(str_append, s, *j, *i - *j))
		return(0);
	*j = *i + 1;
	while (q && s[*i])
	{
		*i += 1;
		if (s[*i] == q && s[*i - 1] != '\\')
		{
			if (!stnjf(str_append, s, *j, *i - *j))
				return (0);
			q = 0;
			*j = *i + 1;
		}
		else if ((s[*i] == '\'' || s[*i] == '\"') && s[*i - 1] == '\\')
		{
			if (!stnjf(str_append, s, *j, (*i - 1) - *j))
				return (0);
			*j = *i;
		}
	}
	return ((!s[*i]) ? 0 : 1);  //Si on est a !s[i] et qu on a pas la derniere quote error multiligne
}

//On va chercher a etre dans un mot metre "" ou '', si on trouve une quote on verifie qu'il n'y a pas de \ devant
//Il faut join a chaque fois sans prendre en compte le \ ou les ' "
char	**ft_quotes(int *i, char **tab, char *s, char c)
{
	int		j;
	char	*str_append;

	str_append = NULL;
	j = *i;
	while (s[*i] != c && s[*i])
	{
		if ((s[*i] == '\'' || s[*i] == '\"'))
		{
			if (*i > 0 && s[*i - 1] == '\\')
			{
				if (!stnjf(&str_append, s, j, (*i - 1) - j))
					return (0); //attention a free
				j = *i;
			}
			else
				if (!ft_in_quotes(i, &j, s, &str_append))
					return (NULL); // attention a free
		}
		*i += 1;
	}
	if (!stnjf(&str_append, s, j, *i - j))
		return (NULL); //Attention free
	return (ft_append(tab, str_append));
}

//On boucle sur la chaine de parametres, etape 1 on skip les espaces ensuite on traite le mot dans ft_quotes
char	**ft_splitq(char *s, char c)
{
	int		i;
	char	**tab;
	char 	**tmp;

	i = 0;
	tab = NULL;
	if (!s)
		return (ft_append(NULL, NULL));
	while (s[i])
	{
		while (s[i] == c)
			i++;
		tmp = tab;
		if (!(tab = ft_quotes(&i, tab, s, c)))
		{
			free_tab(tmp, 1, 1);
			return (ft_append(tab, NULL));
		}
		free_tab(tmp, 1, 0);
	}
	/*tmp = tab;
	tab = ft_append(tab, NULL);
	free_tab(tmp, 1, 0);*/
	return (tab);
}
