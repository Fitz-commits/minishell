/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:14:04 by judecuyp          #+#    #+#             */
/*   Updated: 2020/03/14 22:17:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen_g(const char *s)
{
	unsigned int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int			ft_strchr_g(const char *s, int c)
{
	while (*s != c)
	{
		if (*s == 0)
			return (0);
		s++;
	}
	return (1);
}

char		*ft_substr_g(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	i = 0;
	if (!s)
		return (NULL);
	if (!(str = malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	if (ft_strlen_g(s) > start)
	{
		while (i < len && s[start + i])
		{
			str[i] = s[start + i];
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}

char		*ft_strdup_g(const char *s1)
{
	char	*str;
	char	*ptrstr;

	if (!(str = (char *)malloc((ft_strlen_g(s1) + 1) * sizeof(char))))
		return (0);
	ptrstr = str;
	while (*s1)
		*str++ = *s1++;
	*str = '\0';
	return (ptrstr);
}

char		*ft_strjoin_g(char *s1, char *s2)
{
	char	*str;
	char	*ptr_str;
	int		i;

	i = ft_strlen_g(s1);
	if (!s2)
		return (NULL);
	if (!(str = (char *)malloc((i + ft_strlen_g(s2) + 1) * sizeof(char))))
		return (NULL);
	ptr_str = str;
	if (s1)
		while (*s1)
			*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (ptr_str);
}
