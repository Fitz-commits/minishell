/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 23:22:13 by marvin            #+#    #+#             */
/*   Updated: 2020/03/26 23:22:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, int start, size_t len)
{
	char	*str;
	char	*ptr_str;
	size_t	i;

	i = 0;
	if (!s2)
		return (NULL);
	if (!(str = (char *)malloc((ft_ilen(s1) + len + 1))))
		return (NULL);
	ptr_str = str;
	if (s1)
		while (*s1)
			*str++ = *s1++;
	while (i < len && s2[start + i])
	{
		*str++ = s2[start + i];
		i++;
	}
	*str = '\0';
	return (ptr_str);
}
