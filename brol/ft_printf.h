/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 20:32:11 by judecuyp          #+#    #+#             */
/*   Updated: 2020/03/03 19:18:46 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_printf_list
{
	int		count;
	char	*str;
	int		i;
	int		z;
	int		left;
	int		p;
	int		min;
	int		max;
	int		r;
	int		pass;
	int		*t_pass;
}				t_plist;

typedef struct	s_sizenum
{
	int spaces;
	int len;
	int zero;
	int i;
	int size;
}				t_sizenum;

int				fpf(unsigned int fd, const char *format, ...);
char			*ft_utoa_pf(unsigned int nbr, t_plist *s);
char			*ft_itoa_pf(int nbr, t_plist *s);
char			*ft_llutoah_pf(long long unsigned int nbr, char *base);
char			*ft_itoah_pf(unsigned int nbr, char *base, t_plist *s);
char			*ft_zero_pf(t_plist *s);
int				ft_p_pf(va_list ap, t_plist *s);
int				ft_jtf_pf(char **s, char *s2, int i);
int				ft_free_pf(char **str, int r);
int				ft_free2_pf(char **str, va_list ap, int r);
int				ft_ifree_pf(int **tab, int r);
int				ft_sfree_pf(t_plist *s, int r);
int				ft_spaces_pf(t_plist *s, char *stri, int t);
char			*ft_strnjoin_pf(char const *s1, char const *s2,
	int start, size_t len);
int				ft_intjoin_pf(int **t1, int size, int nb);
char			*ft_strjoin_pf(char const *s1, char const*s2, int i);
int				ft_jtf_pf(char **s, char *s2, int i);
int				ft_jtnf_pf(char **s, char const *format, int start, size_t len);
int				ft_strlen_pf(const char *s);
int				ft_strlen_pass_pf(char *str, t_plist *s);
int				ft_putstr_pf(unsigned int fd, char *str, t_plist *s);
int				ft_atoi_pf(const char *nptr, int *res);
int				ft_num_flags_pf(char *str, t_plist *s);
int				ft_acc_pf(t_plist *s, char *str);
int				ft_c_pf(va_list ap, t_plist *s, char flag);
int				ft_s_pf(va_list ap, t_plist *s);
int				ft_num_pf(va_list ap, t_plist *s, const char *format);

#endif
