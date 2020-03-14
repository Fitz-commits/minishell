/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:06:40 by judecuyp          #+#    #+#             */
/*   Updated: 2020/03/14 02:39:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *b2;
	unsigned char c2;

	c2 = (unsigned char)c;
	b2 = (unsigned char *)b;
	while (len-- > 0)
	{
		*b2 = c2;
		b2++;
	}
	return (b);
}
