/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:33:34 by chris             #+#    #+#             */
/*   Updated: 2020/11/07 12:03:37 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_fperm(t_mshl *m, char *path, struct stat *test)
{
	struct stat			buffer;
	mode_t				perm;

	if (test)
		buffer = *test;
	if (!(test) && ((stat(path, &buffer)) == -1))
		return (set_err(m, 127, 1, path, strerror(ENOENT)));
	perm = buffer.st_mode;
	if ((S_ISDIR(perm)))
		return (set_err(m, 126, 1, path, "is a directory"));
	if ((S_IXUSR & perm) && test)
		return (EXIT_SUCCESS);
	else if ((0444 & perm) && !test && (S_IXUSR & perm))
		return (EXIT_SUCCESS);
	return (set_err(m, 126, 1, path, strerror(EACCES)));
}

int			check_dperm(t_mshl *m, char *path)
{
	struct stat		buffer;
	mode_t			perm;

	if (((stat(path, &buffer)) == -1))
		set_err(m, 127, 1, path, strerror(ENOENT));
	perm = buffer.st_mode;
	if ((!(perm & S_IRWXU)) || !(perm & S_IXUSR))
		(set_err(m, 126, 1, path, strerror(EACCES)));
	if (!(S_ISDIR(buffer.st_mode)))
		(set_err(m, 1, 1, path, strerror(EISDIR)));
	return (EXIT_SUCCESS);
}
