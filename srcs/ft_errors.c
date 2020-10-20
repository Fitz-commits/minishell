#include "minishell.h"

void    print_errno(t_mshl *m, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	if (m->errarg > 0)
	{
		ft_putstr_fd(m->cpargs[m->errarg], 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(errno), 2);
}

void	print_error(t_mshl *m)
{
	ft_putstr_fd("minishell: ", 2);
	if (m->err != 2)
	{   
		ft_putstr_fd(m->args[0], 2);
		ft_putstr_fd(": ", 2);
		if (m->errarg >= 0)
		{
			if (m->err == 9)
				ft_putstr_fd("`", 2);
			ft_putstr_fd(m->args[m->errarg], 2);
			if (m->err == 9)
				ft_putstr_fd("\'", 2);
			ft_putstr_fd(": ", 2);
			m->errarg = -1;
		}
	}
}
// Neeed to refactor this
int		main_error(t_mshl *m)
{
	if (m->err == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("parsing error near : ", 2);
		write(2, &m->cerr, 1);
		write(2, &"\n", 1);
		reat_crval(m, 2);
	}
	if (m->err == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("not implemented near : ", 2);
		write(2, &m->cerr, 1);
		write(2, &"\n", 1);
		reat_crval(m, 1);
	}
	if (m->err == 4)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("unexpected end of file", 2);
		write(2, &"\n", 1);
		reat_crval(m, 2);
	}
	else
		if (errno)
			print_errno(m, NULL); //memory error
	if (m->buf_cmd)
		free(m->buf_cmd);
	m->buf_cmd = NULL;
	set_zpb(m);
	clear_std(m);
	close_pipes(m);
	clean_args(m);
	return (0);
}

int    ft_error(t_mshl *m)
{
	int ret;

	ret = m->err;
	if (m->err == 9 || m->err == 6 || m->err == -10)
		ret = 1;
	if (errno && !m->err)
	{
		print_errno(m, m->cpargs[0]);
		reat_crval(m, 1);
		errno = 0;
	}
	else if (m->err && m->err != 4)
	{
		if (m->err > 0)
			print_error(m);
		if (m->err == 1)
			ft_putstr_fd("Not Implemented\n", 2);
		if (m->err == 2)
			ft_putstr_fd("Parsing Error\n", 2);
		if (m->err == 3)
			ft_putstr_fd("Memory Error\n", 2);
		if (m->err == 6)
			ft_putstr_fd("No such file or directory\n", 2);
		if (m->err == 7)
			ft_putstr_fd("Permission denied\n", 2);
		if (m->err == 9)
			ft_putstr_fd("not a valid identifier\n", 2);
		if (m->err == 127)
			ft_putstr_fd("command not found\n", 2);
		m->err = 0;
		reat_crval(m, ret);
	}
	errno = 0;
	return (ret);
}