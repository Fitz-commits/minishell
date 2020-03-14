/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 06:40:45 by judecuyp          #+#    #+#             */
/*   Updated: 2020/01/29 14:01:19 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		ft_pright(char *stri, char **str, t_sizenum *n)
{
	char *tmp;

	if (!(tmp = (char *)malloc(n->size + 1)))
		return (0);
	tmp[n->size] = '\0';
	while (n->spaces--)
		tmp[n->len++] = ' ';
	if (stri[0] == '-')
		tmp[n->len++] = '-';
	while (n->zero--)
		tmp[n->len++] = '0';
	n->i = (stri[0] == '-') ? 1 : 0;
	while (stri[n->i])
		tmp[n->len++] = stri[n->i++];
	*str = tmp;
	return (1);
}

static int		ft_pleft(char *stri, char **str, t_sizenum *n)
{
	char *tmp;

	if (!(tmp = (char *)malloc(n->size + 1)))
		return (0);
	tmp[n->size] = '\0';
	if (stri[0] == '-')
		tmp[n->len++] = '-';
	while (n->zero--)
		tmp[n->len++] = '0';
	n->i = (stri[0] == '-') ? 1 : 0;
	while (stri[n->i])
		tmp[n->len++] = stri[n->i++];
	while (n->spaces--)
		tmp[n->len++] = ' ';
	*str = tmp;
	return (1);
}

static int		ft_acc_num(char *stri, t_plist *s)
{
	t_sizenum	n;
	char		*str;

	n.len = ft_strlen_pf(stri);
	if ((n.size = n.len) && stri[0] == '-')
		n.size--;
	n.zero = (s->max > n.size) ? s->max - n.size : 0;
	n.spaces = (s->min > n.zero + n.len) ? s->min - (n.len + n.zero) : 0;
	n.size = n.len + n.zero + n.spaces;
	n.len = 0;
	if (s->left)
	{
		if (!(ft_pleft(stri, &str, &n)))
			return (0);
	}
	else
	{
		if (!(ft_pright(stri, &str, &n)))
			return (0);
	}
	if (!(ft_jtf_pf(&s->str, str, 2)))
		return (0);
	free(str);
	return (1);
}

static int		ft_spaces_nb(t_plist *s, char *stri)
{
	int i;

	i = 0;
	if (stri[i] == '-' && s->z)
	{
		if (!(ft_jtf_pf(&s->str, "-", 1)))
			return (0);
		i++;
	}
	if (s->min > -1 && !s->left)
		if (!(ft_spaces_pf(s, stri, 1)))
			return (0);
	if (!(ft_jtf_pf(&s->str, &stri[i], 2)))
		return (0);
	if (s->left && s->min > 0)
		if (!(ft_spaces_pf(s, stri, 1)))
			return (0);
	return (1);
}

int				ft_num_flags_pf(char *str, t_plist *s)
{
	if (s->p && s->max >= 0)
	{
		if (!(ft_acc_num(str, s)))
			return (-1);
	}
	else if ((!s->p && s->min > 0) || (s->p && s->max < 0))
	{
		if (!(ft_spaces_nb(s, str)))
			return (-1);
	}
	else
	{
		if (!(ft_jtf_pf(&s->str, str, 2)))
			return (-1);
	}
	return (ft_free_pf(&str, 1));
}
