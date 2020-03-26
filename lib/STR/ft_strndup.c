/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:34:26 by cdelaby           #+#    #+#             */
/*   Updated: 2019/10/07 15:34:33 by cdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *src, size_t n)
{
	char *dest;

	if (!(dest = malloc(sizeof(char) * (n + 1))))
		return (0);
	dest = ft_strncpy(dest, src, n);
	dest[n] = 0;
	return (&*dest);
}
