/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 05:08:04 by judecuyp          #+#    #+#             */
/*   Updated: 2020/01/29 13:55:50 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_spaces_nb_p(t_plist *s, char *stri)
{
	if (s->z)
		if (!(ft_jtf_pf(&s->str, "0x", 2)))
			return (0);
	if (s->min > -1 && !s->left)
		if (!(ft_spaces_pf(s, stri, 2)))
			return (0);
	if (!s->z)
	{
		if (!(ft_jtf_pf(&s->str, "0x", 2)))
			return (0);
	}
	if (!(ft_jtf_pf(&s->str, stri, 2)))
		return (0);
	if (s->left && s->min > 0)
		if (!(ft_spaces_pf(s, stri, 2)))
			return (0);
	return (1);
}

static int	ft_pright_p(char *stri, char **str, t_sizenum *n)
{
	char *tmp;

	if (!(tmp = (char *)malloc(n->size + 1)))
		return (0);
	tmp[n->size] = '\0';
	while (n->spaces--)
		tmp[n->len++] = ' ';
	tmp[n->len++] = '0';
	tmp[n->len++] = 'x';
	while (n->zero--)
		tmp[n->len++] = '0';
	n->i = 0;
	if (stri)
		while (stri[n->i])
			tmp[n->len++] = stri[n->i++];
	*str = tmp;
	return (1);
}

static int	ft_pleft_p(char *stri, char **str, t_sizenum *n)
{
	char *tmp;

	if (!(tmp = (char *)malloc(n->size + 1)))
		return (0);
	tmp[n->size] = '\0';
	tmp[n->len++] = '0';
	tmp[n->len++] = 'x';
	while (n->zero--)
		tmp[n->len++] = '0';
	n->i = 0;
	if (stri)
		while (stri[n->i])
			tmp[n->len++] = stri[n->i++];
	while (n->spaces--)
		tmp[n->len++] = ' ';
	*str = tmp;
	return (1);
}

static int	ft_acc_p(char *strh, t_plist *s)
{
	t_sizenum	n;
	char		*str;

	n.size = ft_strlen_pf(strh);
	n.len = n.size + 2;
	n.zero = (s->max > n.size) ? s->max - n.size : 0;
	n.spaces = (s->min > n.zero + n.len) ? s->min - (n.len + n.zero) : 0;
	n.size = n.len + n.zero + n.spaces;
	n.len = 0;
	if (s->left)
	{
		if (!(ft_pleft_p(strh, &str, &n)))
			return (0);
	}
	else
	{
		if (!(ft_pright_p(strh, &str, &n)))
			return (0);
	}
	if (!(ft_jtf_pf(&s->str, str, 2)))
		return (0);
	free(str);
	return (1);
}

int			ft_p_pf(va_list ap, t_plist *s)
{
	char *strh;

	if (!(strh = ft_llutoah_pf(va_arg(ap, long long unsigned int),
		"0123456789abcdef")))
		return (-1);
	if (ft_strlen_pf(strh) == 1 && strh[0] == '0' && s->p && s->max == 0)
	{
		free(strh);
		strh = NULL;
	}
	if (s->p && s->max >= 0)
	{
		if (!(ft_acc_p(strh, s)))
			return (-1);
	}
	else
	{
		if (!(ft_spaces_nb_p(s, strh)))
			return (-1);
	}
	return (ft_free_pf(&strh, 1));
}
