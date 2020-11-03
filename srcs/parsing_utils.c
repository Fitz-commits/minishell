#include "minishell.h"

int check_chev_o(t_mshl *m, char *str, int i)
{
    if (!ft_strncmp(&str[i], "<|", 2) || !ft_strncmp(&str[i], "<>", 2)
    || !ft_strncmp(&str[i], "< <", 3) || !ft_strncmp(&str[i], "< ;", 3))
    {
        m->cerr = str[i];
        return (2);
    }
    if (!ft_strncmp(&str[i], "<<", 2))
    {
        m->cerr = str[i];
        return (1);
    }
    return (0);
}

int check_pipe(t_mshl *m, char *str, int i)
{
	if (!ft_strncmp(&str[i], "|>", 2) || !ft_strncmp(&str[i], "|<", 2)
	|| !ft_strncmp(&str[i], "| ;", 3) || !ft_strncmp(&str[i], "|;", 2))
	{
		m->cerr = str[i];
		return (2);
	}
	if (!ft_strncmp(&str[i], "||", 2))
	{
		m->cerr = str[i];
		return (1);
	}
	return (0);
}

int check_dq(t_mshl *m, char *str, int i)
{
    if (!ft_strncmp(&str[i], "; ;", 3) || !ft_strncmp(&str[i], ";;", 2))
    {
        m->cerr = str[i];
        return (2);
    }
    return (0);
}

int check_chev_f(t_mshl *m, char *str, int i)
{
	if (!ft_strncmp(&str[i], ">|", 2) || !ft_strncmp(&str[i], "><", 2) ||
	!ft_strncmp(&str[i], ">>>", 3) || !ft_strncmp(&str[i], "> >", 3) ||
	!ft_strncmp(&str[i], "> ;", 3))
	{
        m->cerr = str[i];
        return (2);
    }
	return (0);
}

int check_pni_errors(t_mshl *m, char *str, int i)
{
    if (str[i] == ';')
        return(check_dq(m, str, i));
    if (str[i] == '<')
        return (check_chev_o(m, str, i));
    if (str[i] == '>')
        return (check_chev_f(m, str, i));
	if (str[i] == '|')
		return (check_pipe(m, str, i));
	if (str[i] == '*' || !ft_strncmp(&str[i], "&&", 2) || str[i] == '&')
	{
		m->cerr = str[i];
		return (1);
	}
	return (0);
}
