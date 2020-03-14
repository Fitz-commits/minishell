/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 20:07:44 by judecuyp          #+#    #+#             */
/*   Updated: 2019/10/15 18:15:56 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*srcs;

	dest = (unsigned char *)dst;
	srcs = (unsigned char *)src;
	if (dst == src)
		return (NULL);
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dest > srcs)
		while (len > 0)
		{
			dest[len - 1] = srcs[len - 1];
			len--;
		}
	else
		while (len--)
			*dest++ = *srcs++;
	return (dst);
}
