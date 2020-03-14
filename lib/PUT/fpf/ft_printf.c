/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:37:59 by judecuyp          #+#    #+#             */
/*   Updated: 2020/03/03 17:02:04 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		ft_initialize(t_plist *s, int c)
{
	if (c == 1)
	{
		s->count = 0;
		s->str = NULL;
		s->i = 0;
		s->r = 0;
		s->pass = -1;
		s->t_pass = NULL;
	}
	s->z = 0;
	s->left = 0;
	s->p = 0;
	s->min = 0;
	s->max = 0;
}

static int		choice(va_list ap, const char *f, t_plist *s)
{
	int i;

	i = 0;
	i += ((f[s->i] == 'c' || f[s->i] == '%') ? ft_c_pf(ap, s, f[s->i]) : 0);
	i += ((f[s->i] == 's') ? ft_s_pf(ap, s) : 0);
	i += ((f[s->i] == 'p') ? ft_p_pf(ap, s) : 0);
	i += ((f[s->i] == 'd' || f[s->i] == 'i' || f[s->i] == 'u' ||
			f[s->i] == 'x' || f[s->i] == 'X') ? ft_num_pf(ap, s, f) : 0);
	if (i < 0)
		return (-1);
	ft_initialize(s, 2);
	return ((!i) ? 0 : 1);
}

static int		ft_flags_more(va_list ap, const char *f, t_plist *s)
{
	if (f[s->i] == '*')
	{
		s->min = va_arg(ap, int);
		if (s->min < 0)
		{
			s->left = 1;
			s->z = 0;
			s->min *= -1;
		}
		s->i++;
	}
	if (f[s->i] >= 48 && f[s->i] <= 57)
		s->i += ft_atoi_pf(&f[s->i], &s->min);
	if (f[s->i] == '.')
	{
		s->p = 1;
		s->i++;
		s->i += ft_atoi_pf(&f[s->i], &s->max);
		if (f[s->i] == '*')
		{
			s->max = va_arg(ap, int);
			s->i++;
		}
	}
	return (choice(ap, f, s));
}

static int		ft_flags(va_list ap, const char *f, t_plist *s)
{
	while (f[s->i] == '-')
	{
		s->left = 1;
		s->i++;
	}
	while (f[s->i] == '0')
	{
		if (f[++s->i] != '-' && !s->left)
			s->z = 1;
		if (f[s->i] == '-')
		{
			s->i++;
			s->left = 1;
		}
	}
	return (ft_flags_more(ap, f, s));
}

int				fpf(unsigned int fd, const char *format, ...)
{
	int		j;
	t_plist	s;
	va_list ap;

	ft_initialize(&s, 1);
	va_start(ap, format);
	while (!(j = 0) && format[s.i])
	{
		while (format[s.i + j] != '%' && format[s.i + j])
			j++;
		if (!(ft_jtnf_pf(&s.str, format, s.i, j)))
			return (ft_free2_pf(&s.str, ap, -1));
		s.i += j;
		if (format[s.i] == '%')
		{
			s.i++;
			if ((s.r = ft_flags(ap, format, &s)) <= 0)
				return (ft_free2_pf(&s.str, ap, -1));
			s.i++;
		}
	}
	va_end(ap);
	s.count = ft_putstr_pf(fd, s.str, &s);
	return (ft_sfree_pf(&s, s.count));
}
