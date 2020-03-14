/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:41:10 by judecuyp          #+#    #+#             */
/*   Updated: 2019/10/22 16:00:45 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int			is_charset(char c, char const *set)
{
	int i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

static size_t		find_i_min(char const *s1, char const *set)
{
	size_t i;

	i = 0;
	while (is_charset(s1[i], set))
		i++;
	return (i);
}

static size_t		find_i_max(char const *s1, char const *set)
{
	size_t i;

	i = ft_strlen(s1);
	if (!i)
		return (i);
	i--;
	while (i > 0 && is_charset(s1[i], set))
		i--;
	return (i);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	size_t		i_start;
	size_t		i_end;
	char		*str;
	char		*ptr_str;

	if (!s1 || !set)
		return (NULL);
	i_start = find_i_min(s1, set);
	if (!(i_end = find_i_max(s1, set)))
		i_end = i_start;
	if (!(str = (char *)malloc(((i_end - i_start) + 2) * sizeof(char))))
		return (0);
	ptr_str = str;
	while (i_start <= i_end)
		*str++ = s1[i_start++];
	*str = 0;
	return (ptr_str);
}
