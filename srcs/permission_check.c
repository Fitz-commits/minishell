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

int		check_fperm(t_mshl *m, char *path)
{
	struct stat buffer;
    mode_t perm;

    if (((stat(path, &buffer)) == -1)) // set erreur
    {
        m->errarg = m->progr - 1;
        return (EXIT_FAILURE);
    }
	perm = buffer.st_mode;
    if (!((perm & S_IEXEC)))
    {
        m->err = 126;
        m->ierr = m->begin;
		return (EXIT_FAILURE); //not authorized	
    }
	if ((S_ISDIR(buffer.st_mode)))
    {
        m->err = 12;
        m->ierr = m->progr;
		return (EXIT_FAILURE); //is not a dir
    }
	return (EXIT_SUCCESS);
}

int		check_dperm(t_mshl *m, char *path)
{
	struct stat buffer;
	mode_t perm;
	
	if (((stat(path, &buffer)) == -1)) // set erreur
    {
        m->errarg = m->progr - 1;
        return (EXIT_FAILURE);
    }
	perm = buffer.st_mode;
    if ((!(perm & S_IRWXU)) || !(perm &  S_IXUSR))
    {
        m->err = 7;
        m->ierr = m->begin;
        m->errarg = 1;
		return (EXIT_FAILURE); //not authorized	
    }
	if (!(S_ISDIR(buffer.st_mode)))
    {
        m->err = 6;
        m->ierr = m->progr;
		return (EXIT_FAILURE); //is not a dir
    }
	return (EXIT_SUCCESS);
}