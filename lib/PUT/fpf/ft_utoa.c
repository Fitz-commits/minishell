/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:32:38 by judecuyp          #+#    #+#             */
/*   Updated: 2020/01/29 14:08:12 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		ft_memory3(unsigned int nb)
{
	int cmpt;

	cmpt = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		cmpt++;
	}
	return (cmpt);
}

static char		*ft_putnbr_char2(unsigned int nb,
	char *tab_nbr, int cmpt_memory)
{
	char	*base;

	base = "0123456789";
	if (nb > 9)
		ft_putnbr_char2(nb / 10, tab_nbr, cmpt_memory - 1);
	tab_nbr[cmpt_memory] = base[nb % 10];
	return (tab_nbr);
}

char			*ft_utoa_pf(unsigned int nbr, t_plist *s)
{
	unsigned int	nb;
	int				cmpt_memory;
	char			*tab_nbr;

	cmpt_memory = 0;
	if (nbr == 0)
	{
		if (!(tab_nbr = ft_zero_pf(s)))
			return (NULL);
	}
	else
	{
		nb = nbr;
		cmpt_memory += ft_memory3(nb);
		if (!(tab_nbr = (char *)malloc((cmpt_memory + 1) * sizeof(char))))
			return (NULL);
		if (nbr == 0)
			tab_nbr[0] = ' ';
		else
			tab_nbr = ft_putnbr_char2(nb, tab_nbr, cmpt_memory - 1);
		tab_nbr[cmpt_memory] = '\0';
	}
	return (tab_nbr);
}
