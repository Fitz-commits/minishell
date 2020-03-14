/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:08:16 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/05 13:06:27 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_free(char **str, int r)
{
	if (!str || !*str)
		return (r);
	free(*str);
	str = NULL;
	return (r);
}

static int		ft_i_dup(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

static int		gnl_ret(char *tab[OPEN_MAX + 1], int fd, char **line)
{
	int		i;
	char	*tmp;

	i = ft_i_dup(tab[fd]);
	if (!(!i || (i == 0 && !tab[fd][0])))
	{
		free(*line);
		if (!(*line = ft_substr_g(tab[fd], 0, i)))
			return (-1);
	}
	if (tab[fd] && tab[fd][i] == '\n')
		i++;
	tmp = tab[fd];
	if (tab[fd] && !(tab[fd] = ft_strdup_g(&tab[fd][i])))
		return (ft_free(&tmp, -1));
	ft_free(&tmp, 1);
	if ((tab[fd] && !tab[fd][0]) || !(tab[fd]))
	{
		free(tab[fd]);
		tab[fd] = NULL;
		return (0);
	}
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char		*tab[OPEN_MAX + 1];
	char			reader[BUFFER_SIZE + 1];
	char			*tmp;
	int				ret;
	int				test;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || !line)
		return (-1);
	if ((ret = 1) && (!tab[fd] || (tab[fd] && !ft_strchr_g(tab[fd], '\n'))))
		while ((ret = read(fd, reader, BUFFER_SIZE)) > 0)
		{
			reader[ret] = '\0';
			tmp = tab[fd];
			if (!(tab[fd] = ft_strjoin_g(tab[fd], reader)))
				return (ft_free(&tmp, -1));
			ft_free(&tmp, 1);
			if (ft_strchr_g(reader, '\n'))
				break ;
		}
	if ((*line = ft_strdup_g("")) && ret < 0)
		return (-1);
	if (!(test = gnl_ret(tab, fd, line)) && ret == 0)
		return (0);
	else
		return ((test == -1) ? -1 : 1);
}
