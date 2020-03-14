/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 06:29:35 by judecuyp          #+#    #+#             */
/*   Updated: 2020/01/29 13:49:31 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_strnjoin_pf(char const *s1, char const *s2, int start, size_t len)
{
	char	*str;
	char	*ptr_str;
	size_t	i;

	i = 0;
	if (!s2)
		return (NULL);
	if (!(str = (char *)malloc((ft_strlen_pf(s1) + len + 1) * sizeof(char))))
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

int		ft_intjoin_pf(int **t1, int size, int nb)
{
	int i;
	int *tab;
	int *tmp;

	tmp = *t1;
	if (!(tab = (int *)malloc(size * sizeof(int))))
		return (0);
	i = 0;
	if (*t1)
		while (i < size - 1)
		{
			tab[i] = *t1[i];
			i++;
		}
	tab[i] = nb;
	*t1 = tab;
	return (ft_ifree_pf(&tmp, 1));
}

char	*ft_strjoin_pf(char const *s1, char const *s2, int i)
{
	char	*str;
	char	*ptr_str;

	if (!s2)
		return (NULL);
	if (!(str = (char *)malloc((ft_strlen_pf(s1)
		+ ft_strlen_pf(s2) + 1) * sizeof(char))))
		return (NULL);
	ptr_str = str;
	if (s1)
		while (*s1)
			*str++ = *s1++;
	if (i == 1)
		*str++ = *s2;
	else
		while (*s2)
			*str++ = *s2++;
	*str = '\0';
	return (ptr_str);
}

int		ft_jtf_pf(char **s, char *s2, int i)
{
	char *tmp;

	tmp = *s;
	if (!(*s = ft_strjoin_pf(*s, s2, i)))
		return (ft_free_pf(&tmp, 0));
	return (ft_free_pf(&tmp, 1));
}

int		ft_jtnf_pf(char **s, char const *format, int start, size_t len)
{
	char *tmp;

	tmp = *s;
	if (!(*s = ft_strnjoin_pf(*s, format, start, len)))
		return (ft_free_pf(&tmp, 0));
	return (ft_free_pf(&tmp, 1));
}
