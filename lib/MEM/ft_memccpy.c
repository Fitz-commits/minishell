/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:43:24 by judecuyp          #+#    #+#             */
/*   Updated: 2019/10/15 18:14:35 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*srcs;
	unsigned char	cc;

	cc = (unsigned char)c;
	dest = (unsigned char *)dst;
	srcs = (unsigned char *)src;
	while (n--)
	{
		if (*srcs == cc)
		{
			*dest = *srcs;
			return (++dest);
		}
		*dest = *srcs;
		dest++;
		srcs++;
	}
	return (0);
}
