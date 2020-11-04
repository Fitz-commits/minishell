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

// int		check_rperm(t_mshl *m, char *path)
// {
// 	return (EXIT_SUCCESS);
// }

// int		check_wperm(t_mshl *m, char *path)
// {
// 	return (EXIT_SUCCESS);
// }

int		check_fperm(t_mshl *m, char *path, struct stat *test)
{
	struct stat buffer;
    mode_t perm;

    if (test)
        buffer = *test;
    if (!(test) && ((stat(path, &buffer)) == -1)) // set erreur
        return (set_err(m, 127, 1, path, strerror(ENOENT)));
	perm = buffer.st_mode;
    if ((S_ISDIR(perm)))
		return (set_err(m, 126, 1, path, "is a directory")); //isa dir
    if ((S_IXUSR & perm) && test)
		return (EXIT_SUCCESS); //not authorized	
    else if ((0444 & perm) && !test && (S_IXUSR & perm))
        return (EXIT_SUCCESS);
	return (set_err(m, 126, 1, path, strerror(EACCES)));
}

int		check_dperm(t_mshl *m, char *path)
{
	struct stat buffer;
	mode_t perm;
	
	if (((stat(path, &buffer)) == -1)) // set erreur
        set_err(m, 127, 1, path, strerror(ENOENT));
	perm = buffer.st_mode;
    if ((!(perm & S_IRWXU)) || !(perm &  S_IXUSR))
        (set_err(m, 126, 1, path, strerror(EACCES)));
	if (!(S_ISDIR(buffer.st_mode)))
        (set_err(m, 1, 1, path, strerror(EISDIR)));
	return (EXIT_SUCCESS);
}
