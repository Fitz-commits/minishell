/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 18:51:03 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/28 18:11:08 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*ptr_str;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char *)malloc(ft_ilen(s1) + ft_ilen(s2) + 1)))
		return (0);
	ptr_str = str;
	if (s1)
		while (*s1)
			*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (ptr_str);
}
