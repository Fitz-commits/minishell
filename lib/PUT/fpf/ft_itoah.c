/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoah.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 19:03:51 by judecuyp          #+#    #+#             */
/*   Updated: 2020/01/29 13:49:43 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			cmpt_letter_pf(unsigned int nbr)
{
	int i;

	i = 0;
	while (nbr >= 16)
	{
		i++;
		nbr /= 16;
	}
	i += 1;
	return (i);
}

char		*ft_itoah_pf(unsigned int nbr, char *base, t_plist *s)
{
	int				i;
	char			*str;

	i = cmpt_letter_pf(nbr);
	if (nbr == 0)
	{
		if (!(str = ft_zero_pf(s)))
			return (NULL);
	}
	else
	{
		if (!(str = (char *)malloc((i + 1) * sizeof(char))))
			return (NULL);
		str[i] = '\0';
		i--;
		while (nbr >= 16)
		{
			str[i] = base[nbr % 16];
			i--;
			nbr /= 16;
		}
		str[i] = base[nbr % 16];
	}
	return (str);
}
