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

/*int		ft_quotes(int *i, int *j)
{
	int q;

	q = 0;
}*/

char	**ft_splitq(char *s, char c)
{
	int		i;
	int		j;
	char	**tab;
	char	*str_append;
	char	q;
	char 	*tmp;
	char	**tmp2;

	i = 0;
	q = 0;
	if (!s)
		return (ft_append(NULL, NULL));
	tab = NULL;
	str_append = NULL;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] != c && s[i])
		{
			if ((s[i] == '\'' || s[i] == '\"'))
			{
				if (i > 0 && s[i - 1] == '\\')
				{
					tmp = str_append;
					str_append = ft_strnjoin(str_append, s, j, (i - 1) - j);
					free_str(&tmp, 1);
					j = i;
				}
				else
				{
					q = s[i];
					tmp = str_append;
					str_append = ft_strnjoin(str_append, s, j, i - j);
					free_str(&tmp, 1);
					j = i + 1;
					while (q && s[i])
					{
						i++;
						if (s[i] == q && s[i - 1] != '\\')
						{
							tmp = str_append;
							str_append = ft_strnjoin(str_append, s, j, i - j);
							free_str(&tmp, 1);
							q = 0;
							j = i + 1;
						}
						else if (s[i] == q && s[i - 1] == '\\')
						{
							tmp = str_append;
							str_append = ft_strnjoin(str_append, s, j, (i - 1) - j);
							free_str(&tmp, 1);
							j = i;
						}
					}
					if (!s[i])
						return (NULL);
				}
			}	
			i++;
		}
		tmp = str_append;
		str_append = ft_strnjoin(str_append, s, j, i - j);
		free_str(&tmp, 1);
		tmp2 = tab;
		tab = ft_append(tab, str_append);
		free_tab(tmp2, 1);
		free_str(&str_append, 1);
	}
	tmp2 = tab;
	tab = ft_append(tab, NULL);
	free_tab(tmp2, 1);
	free_str(&str_append, 1);
	return (tab);
}
