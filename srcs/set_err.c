#include "minishell.h"
/*
**
**  So ret is the value for $?
**  Option is if you need one or two or three things nothed
**  
** 
**
*/
int set_err(t_mshl *m, int ret, int opt, ...)
{
    va_list ap;

    va_start(ap, opt);
    ft_bzero(m->err_to_print, PATH_MAX + 1);
    ft_strcpy(m->err_to_print, "minishell : ");
    if (opt >= 1)
    {
        ft_strcat(m->err_to_print, va_arg(ap, char*));
        ft_strcat(m->err_to_print, ": ");
    }
    if (opt >= 2)
    {
        ft_strcat(m->err_to_print, va_arg(ap, char*));
        ft_strcat(m->err_to_print, ": ");
    }
    ft_strcat(m->err_to_print, va_arg(ap, char*));
    m->err = ret;
    va_end(ap);
    return (ret);
}