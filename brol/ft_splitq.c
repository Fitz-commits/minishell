/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:30:29 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/15 09:24:49 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
**	this split splits on space and stop the splitting when encountering 
**	a char that is in delimitter and starts again when encountering
**	again another delimitter
*/
#include "./lib/includes/libft.h"
static int 			countquotes(const char *str)
{
	int i;
	i = 0;
	
	if (str[i] != '\'' && str[i] != '\"')
		return 1;
	while (str[++i])
		if (str[i] == str[0])
			return (i);		
	return (1);
}

static int			count(const char *str)
{
	int i;
	int j;

	j = 0;
	i = 0;

	while (str[i])
	{
		if (ft_ispace(str[i]))
		{
			i++;
			continue;
		}
		j++;
		while (str[i] && !ft_ispace(str[i]))
			i += countquotes(&str[i]);
	}
	return (j);
}

static char			**itsfree(char **split, int j)
{
	while (j >= 0)
	{
		ft_bzero((void*)split[j], ft_strlen(split[j]));
		free(split[j]);
		j--;
	}
	free(split);
	return (NULL);
}

char				**ft_splitq(const char *str)
{
	size_t		j;
	size_t		k;
	char		**split;

	j = 0;
	if (str == 0)
		return (0);
	if (!(split = (char**)malloc(sizeof(char*) * (count(str) + 1))))
		return (0);
	while (*str)
	{
		if (ft_ispace(*str))
		{
			str++;
			continue;
		}
		k = 0;
		while (str[k] && !ft_ispace(str[k]))
			k += countquotes(str + k);
		if ((split[j++] = ft_strndup(str, k)) == NULL)
			return (itsfree(split, j));
		str += k;
	}
	split[j] = 0;
	return (split);
}
