#include "minishell.h"

/*
**	I need a function that deals with file
**		file is for path and redirection
**
**	I need another one that deals with directory
**	directory is for cd 
**
**
**
**
*/

/*int		check_fperm(t_mshl *m, char *path, int fdflag)
{
	struct stat buffer;
	return (EXIT_SUCCESS);
}*/

int		check_dperm(t_mshl *m, char *path)
{
	struct stat buffer;
	mode_t perm;
	
	if ((stat(path, &buffer) == -1)) // set erreur
		return (m->ierr = m->begin);
	perm = buffer.st_mode;
	if (!S_ISDIR(buffer.st_mode))
		return ((m->err = 6) && (m->ierr = m->progr)); //is not a dir
	if ((!(perm & S_IRWXU)) && !(perm &  S_IXUSR))
		return ((m->err = 7) && (m->ierr = m->progr)); //not authorized	
	return (EXIT_SUCCESS);
}