/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:24:11 by judecuyp          #+#    #+#             */
/*   Updated: 2020/01/28 17:09:13 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 17
# endif

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

int				get_next_line(int fd, char **line);
size_t			ft_strlen_g(const char *s);
char			*ft_strjoin_g(char *s1, char *s2);
char			*ft_substr_g(char const *s, unsigned int start, size_t len);
char			*ft_strchr_g(const char *s, int c);
char			*ft_strdup_g(const char *s1);
#endif
