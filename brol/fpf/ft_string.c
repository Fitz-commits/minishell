/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 06:58:32 by judecuyp          #+#    #+#             */
/*   Updated: 2020/01/29 14:01:43 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				ft_spaces_pf(t_plist *s, char *stri, int t)
{
	int		len_spaces;
	char	*spaces;
	char	l;
	int		size_ap;

	size_ap = ft_strlen_pf(stri);
	if (t == 2)
		size_ap += 2;
	l = ' ';
	if (s->z)
		l = '0';
	if (size_ap < s->min)
	{
		len_spaces = s->min - size_ap;
		if (!(spaces = (char *)malloc(len_spaces + 1)))
			return (0);
		spaces[len_spaces] = '\0';
		while (--len_spaces >= 0)
			spaces[len_spaces] = l;
		if (!(ft_jtf_pf(&s->str, spaces, 2)))
			return (0);
		free(spaces);
	}
	return (1);
}

static int		ft_acc_s(t_plist *s, char *str, int i, int len)
{
	int		j;
	char	c;
	char	*strg;

	c = ' ';
	if (s->z)
		c = '0';
	j = 0;
	if (!(strg = (char *)malloc(i + 1 * sizeof(char))))
		return (0);
	strg[i] = '\0';
	if (!(i = 0) && !s->left)
		while (i < s->min - len)
			strg[i++] = c;
	while (j < len)
		strg[i++] = str[j++];
	if (s->left && !(j = 0))
		while (j++ < s->min - len)
			strg[i++] = c;
	if (!(ft_jtf_pf(&s->str, strg, 2)))
		return (-1);
	return (ft_free_pf(&strg, 1));
}

int				ft_acc_pf(t_plist *s, char *str)
{
	int		len;
	int		i;

	len = 0;
	while (str[len] && len < s->max)
		len++;
	i = len;
	if (i < s->min)
		i = s->min;
	return (ft_acc_s(s, str, i, len));
}

int				ft_c_pf(va_list ap, t_plist *s, char flag)
{
	char c;

	if (s->min > 1 && !s->left)
		if (!(ft_spaces_pf(s, "a\0", 1)))
			return (-1);
	if (flag == '%')
		c = '%';
	else
		c = va_arg(ap, int);
	if (c == '\0')
	{
		s->pass++;
		if (!ft_intjoin_pf(&s->t_pass, s->pass + 1, ft_strlen_pf(s->str)))
			return (-1);
		c = 'a';
	}
	if (!(ft_jtf_pf(&s->str, &c, 1)))
		return (-1);
	if (s->left && s->min > 0)
		if (!(ft_spaces_pf(s, "a\0", 1)))
			return (-1);
	return (1);
}

int				ft_s_pf(va_list ap, t_plist *s)
{
	char *str;

	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	if (s->p && s->max >= 0)
	{
		if (!(ft_acc_pf(s, str)))
			return (-1);
	}
	else
	{
		if (s->min > -1 && !s->left)
			if (!(ft_spaces_pf(s, str, 1)))
				return (-1);
		if (!(ft_jtf_pf(&s->str, str, 2)))
			return (-1);
		if (s->left && s->min > 0)
			if (!(ft_spaces_pf(s, str, 1)))
				return (-1);
	}
	return (1);
}
